#include "../include/SaveManager.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ====================================
// Save Researcher, Challenges, Modules
// ====================================

bool SaveManager::SaveProgress(
    const Researcher& researcher,
    const std::vector<Challenge>& challenges,
    const std::vector<LearningModule>& learningModules,
    const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cout << "\nError opening save file.\n";
        return false;
    }

    // Save file format version.
    file << "BBT_SAVE_V2\n";

    // Save researcher information.
    file << researcher.GetName() << '\n';
    file << researcher.GetLevel() << '\n';
    file << researcher.GetTotalXP() << '\n';
    file << researcher.GetAvailableXP() << '\n';

    // Save challenge completion.
    file << challenges.size() << '\n';

    for (const Challenge& challenge : challenges)
    {
        file << challenge.IsCompleted() << '\n';
    }

    // Save learning module progress.
    file << learningModules.size() << '\n';

    for (const LearningModule& module : learningModules)
    {
        file << module.IsUnlocked() << ' '
             << module.IsCompleted() << '\n';
    }

    file.close();

    if (file.fail())
    {
        std::cout << "\nError writing save file.\n";
        return false;
    }

    return true;
}

// ====================================
// Load Researcher, Challenges, Modules
// ====================================

bool SaveManager::LoadProgress(
    Researcher& researcher,
    std::vector<Challenge>& challenges,
    std::vector<LearningModule>& learningModules,
    const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "\nNo saved progress found.\n";
        return false;
    }

    std::string version;
    std::string savedName;

    int savedLevel = 0;
    int savedTotalXP = 0;
    int savedAvailableXP = 0;

    // Check save file version.
    if (!std::getline(file, version) ||
        version != "BBT_SAVE_V2")
    {
        std::cout << "\nUnsupported save file format.\n";
        return false;
    }

    // Read researcher name.
    if (!std::getline(file, savedName) ||
        savedName.empty())
    {
        std::cout << "\nInvalid researcher name.\n";
        return false;
    }

    // Read researcher progress.
    if (!(file >> savedLevel
               >> savedTotalXP
               >> savedAvailableXP))
    {
        std::cout << "\nInvalid researcher data.\n";
        return false;
    }

    // Read challenge count.
    std::size_t challengeCount = 0;

    if (!(file >> challengeCount) ||
        challengeCount != challenges.size())
    {
        std::cout << "\nInvalid challenge count.\n";
        return false;
    }

    // Read challenge completion flags.
    std::vector<bool> completedChallenges;

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

    // Read learning module count.
    std::size_t moduleCount = 0;

    if (!(file >> moduleCount) ||
        moduleCount != learningModules.size())
    {
        std::cout << "\nInvalid learning module count.\n";
        return false;
    }

    // Temporary module progress.
    std::vector<bool> unlockedModules;
    std::vector<bool> completedModules;

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

    // Restore researcher XP and level.
    if (!researcher.RestoreProgress(
        savedLevel,
        savedTotalXP,
        savedAvailableXP))
    {
        std::cout << "\nInvalid researcher progress.\n";
        return false;
    }

    // Restore challenges without awarding XP.
    for (std::size_t i = 0; i < challengeCount; i++)
    {
        challenges[i].RestoreCompletion(
            completedChallenges[i]);
    }

    // Restore learning modules without
    // awarding XP or charging unlock costs.
    for (std::size_t i = 0; i < moduleCount; i++)
    {
        learningModules[i].RestoreProgress(
            unlockedModules[i],
            completedModules[i]);
    }

    return true;
}