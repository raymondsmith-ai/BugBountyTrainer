#include "../include/SaveManager.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ====================================
// Save Researcher, Challenges, Modules,
// SQL Fundamentals, and SQL Injection
// ====================================

bool SaveManager::SaveProgress(
    const Researcher& researcher,
    const std::vector<Challenge>& challenges,
    const std::vector<LearningModule>& learningModules,
    const SQLFundamentals& sqlFundamentals,
    const SQLInjection& sqlInjection,
    const SQLAcademy& sqlAcademy,
    const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cout << "\nError opening save file.\n";
        return false;
    }

    // ====================================
    // Save File Version
    // ====================================

    file << "BBT_SAVE_V6\n";

    // ====================================
    // Save Researcher Information
    // ====================================

    file << researcher.GetName() << '\n';
    file << researcher.GetLevel() << '\n';
    file << researcher.GetTotalXP() << '\n';
    file << researcher.GetAvailableXP() << '\n';

    // ====================================
    // Save Challenge Completion
    // ====================================

    file << challenges.size() << '\n';

    for (const Challenge& challenge : challenges)
    {
        file << challenge.IsCompleted() << '\n';
    }

    // ====================================
    // Save Learning Module Progress
    // ====================================

    file << learningModules.size() << '\n';

    for (const LearningModule& module : learningModules)
    {
        file << module.IsUnlocked() << ' '
            << module.IsCompleted() << '\n';
    }

    // ====================================
    // Save SQL Fundamentals Progress
    // ====================================

    file << sqlFundamentals.IsGuidedComplete() << ' '
        << sqlFundamentals.IsAssessmentComplete() << ' '
        << sqlFundamentals.IsRewardClaimed() << '\n';

    // ====================================
    // Save SQL Injection Stage 2 Progress
    // ====================================

    file << sqlInjection.IsLessonComplete() << ' '
        << sqlInjection.IsAssessmentComplete() << ' '
        << sqlInjection.IsRewardClaimed() << '\n';

    // ====================================
    // Save SQL Academy Completion (V6)
    // Store IDs to detect curriculum changes.
    // ====================================

    const std::vector<SQLLesson>& academyLessons = sqlAcademy.GetLessons();
    file << academyLessons.size() << '\n';

    for (const SQLLesson& lesson : academyLessons)
    {
        file << lesson.id << ' ' << lesson.completed << '\n';
    }

    // ====================================
    // Close File and Check for Errors
    // ====================================

    file.close();

    if (file.fail())
    {
        std::cout << "\nError writing save file.\n";
        return false;
    }

    return true;
}

// ====================================
// Load Researcher, Challenges, Modules,
// SQL Fundamentals, and SQL Injection
// ====================================

bool SaveManager::LoadProgress(
    Researcher& researcher,
    std::vector<Challenge>& challenges,
    std::vector<LearningModule>& learningModules,
    SQLFundamentals& sqlFundamentals,
    SQLInjection& sqlInjection,
    SQLAcademy& sqlAcademy,
    const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "\nNo saved progress found.\n";
        return false;
    }

    // ====================================
    // Temporary Save Data
    // ====================================

    std::string version;
    std::string savedName;

    int savedLevel = 0;
    int savedTotalXP = 0;
    int savedAvailableXP = 0;

    // ====================================
    // Validate Save File Version
    // ====================================

    if (!std::getline(file, version) ||
        (version != "BBT_SAVE_V2" &&
            version != "BBT_SAVE_V3" &&
            version != "BBT_SAVE_V4" &&
            version != "BBT_SAVE_V5" &&
            version != "BBT_SAVE_V6"))
    {
        std::cout << "\nUnsupported save file format.\n";
        return false;
    }

    // ====================================
    // Read Researcher Name
    // ====================================

    if (!std::getline(file, savedName) ||
        savedName.empty())
    {
        std::cout << "\nInvalid researcher name.\n";
        return false;
    }

    // ====================================
    // Read Researcher Progress
    // ====================================

    if (!(file >> savedLevel
        >> savedTotalXP
        >> savedAvailableXP))
    {
        std::cout << "\nInvalid researcher data.\n";
        return false;
    }

    // ====================================
    // Read Challenge Count
    // ====================================

    std::size_t challengeCount = 0;

    if (!(file >> challengeCount) ||
        challengeCount != challenges.size())
    {
        std::cout << "\nInvalid challenge count.\n";
        return false;
    }

    // ====================================
    // Read Challenge Completion
    // ====================================

    std::vector<bool> completedChallenges;

    completedChallenges.reserve(challengeCount);

    for (std::size_t i = 0; i < challengeCount; i++)
    {
        int completed = 0;

        if (!(file >> completed) ||
            (completed != 0 && completed != 1))
        {
            std::cout << "\nInvalid challenge data.\n";
            return false;
        }

        completedChallenges.push_back(completed == 1);
    }

    // ====================================
    // Read Learning Module Count
    // ====================================

    std::size_t moduleCount = 0;

    if (!(file >> moduleCount) ||
        moduleCount != learningModules.size())
    {
        std::cout << "\nInvalid learning module count.\n";
        return false;
    }

    // ====================================
    // Read Learning Module Progress
    // ====================================

    std::vector<bool> unlockedModules;
    std::vector<bool> completedModules;

    unlockedModules.reserve(moduleCount);
    completedModules.reserve(moduleCount);

    for (std::size_t i = 0; i < moduleCount; i++)
    {
        int unlocked = 0;
        int completed = 0;

        if (!(file >> unlocked >> completed) ||
            (unlocked != 0 && unlocked != 1) ||
            (completed != 0 && completed != 1))
        {
            std::cout << "\nInvalid module data.\n";
            return false;
        }

        unlockedModules.push_back(unlocked == 1);
        completedModules.push_back(completed == 1);
    }

    // ====================================
    // SQL Fundamentals Temporary Data
    // ====================================

    int savedGuided = 0;
    int savedAssessment = 0;
    int savedRewardClaimed = 0;

    // ====================================
    // Read SQL Fundamentals Progress
    // V3, V4, and V5
    // ====================================

    if (version == "BBT_SAVE_V3" ||
        version == "BBT_SAVE_V4" ||
        version == "BBT_SAVE_V5" ||
        version == "BBT_SAVE_V6")
    {
        if (!(file >> savedGuided >> savedAssessment) ||
            (savedGuided != 0 && savedGuided != 1) ||
            (savedAssessment != 0 && savedAssessment != 1) ||
            (savedAssessment == 1 && savedGuided == 0))
        {
            std::cout << "\nInvalid SQL Fundamentals progress.\n";
            return false;
        }
    }

    // ====================================
    // Read SQL Fundamentals Reward
    // V4 and V5
    // ====================================

    if (version == "BBT_SAVE_V4" ||
        version == "BBT_SAVE_V5" ||
        version == "BBT_SAVE_V6")
    {
        if (!(file >> savedRewardClaimed) ||
            (savedRewardClaimed != 0 &&
                savedRewardClaimed != 1) ||
            (savedRewardClaimed == 1 &&
                savedAssessment == 0))
        {
            std::cout << "\nInvalid SQL Fundamentals reward data.\n";
            return false;
        }
    }

    // ====================================
    // SQL Injection Temporary Data
    // ====================================

    int savedInjectionLesson = 0;
    int savedInjectionAssessment = 0;
    int savedInjectionReward = 0;

    // ====================================
    // Read SQL Injection Stage 2 Progress
    // V5 Only
    // ====================================

    if (version == "BBT_SAVE_V5" ||
        version == "BBT_SAVE_V6")
    {
        if (!(file >> savedInjectionLesson
            >> savedInjectionAssessment
            >> savedInjectionReward) ||
            (savedInjectionLesson != 0 &&
                savedInjectionLesson != 1) ||
            (savedInjectionAssessment != 0 &&
                savedInjectionAssessment != 1) ||
            (savedInjectionReward != 0 &&
                savedInjectionReward != 1) ||
            (savedInjectionAssessment == 1 &&
                savedInjectionLesson == 0) ||
            (savedInjectionReward == 1 &&
                savedInjectionAssessment == 0))
        {
            std::cout << "\nInvalid SQL Injection progress data.\n";
            return false;
        }
    }

    // ====================================
    // Read SQL Academy Completion (V6)
    // Older saves start with all academy modules incomplete.
    // ====================================

    const std::vector<SQLLesson>& academyLessons = sqlAcademy.GetLessons();
    std::vector<bool> savedAcademyCompletion(academyLessons.size(), false);

    if (version == "BBT_SAVE_V6")
    {
        std::size_t academyCount = 0;
        if (!(file >> academyCount) || academyCount != academyLessons.size())
        {
            std::cout << "\nInvalid SQL Academy module count.\n";
            return false;
        }

        for (std::size_t i = 0; i < academyCount; ++i)
        {
            int lessonId = 0;
            int completed = 0;
            if (!(file >> lessonId >> completed) ||
                lessonId != academyLessons[i].id ||
                (completed != 0 && completed != 1) ||
                (completed == 1 && i > 0 && !savedAcademyCompletion[i - 1]))
            {
                std::cout << "\nInvalid SQL Academy progress.\n";
                return false;
            }
            savedAcademyCompletion[i] = (completed == 1);
        }
    }
    // ====================================
// Validate End of Save File
// ====================================

    file >> std::ws;

    if (file.bad())
    {
        std::cout << "\nError reading save file.\n";
        return false;
    }

    if (file.peek() != std::char_traits<char>::eof())
    {
        std::cout << "\nUnexpected data found in save file.\n";
        return false;
    }

    if (file.bad())
    {
        std::cout << "\nError reading save file.\n";
        return false;
    }
    // ====================================
    // Restore Researcher Progress
    // ====================================

    // Validate XP and level before applying
    // the remaining saved progress.

    if (!researcher.RestoreProgress(
        savedLevel,
        savedTotalXP,
        savedAvailableXP))
    {
        std::cout << "\nInvalid researcher progress.\n";
        return false;
    }

    // ====================================
    // Restore Researcher Name
    // ====================================

    researcher.SetName(savedName);

    // ====================================
    // Restore Challenge Completion
    // ====================================

    // Restoring completion does not award XP.

    for (std::size_t i = 0; i < challengeCount; i++)
    {
        challenges[i].RestoreCompletion(
            completedChallenges[i]);
    }

    // ====================================
    // Restore Learning Module Progress
    // ====================================

    // Restoring modules does not award XP
    // or charge module unlock costs.

    for (std::size_t i = 0; i < moduleCount; i++)
    {
        learningModules[i].RestoreProgress(
            unlockedModules[i],
            completedModules[i]);
    }

    // ====================================
    // Restore SQL Fundamentals Progress
    // ====================================

    sqlFundamentals.RestoreProgress(
        savedGuided == 1,
        savedAssessment == 1,
        savedRewardClaimed == 1);

    // ====================================
    // Restore SQL Injection Stage 2
    // ====================================

    sqlInjection.RestoreProgress(
        savedInjectionLesson == 1,
        savedInjectionAssessment == 1,
        savedInjectionReward == 1);

    // Restore academy completion without granting XP.
    for (std::size_t i = 0; i < academyLessons.size(); ++i)
    {
        sqlAcademy.RestoreLessonCompletion(
            academyLessons[i].id, savedAcademyCompletion[i]);
    }

    return true;
}
