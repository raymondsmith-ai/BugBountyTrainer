#include "../include/SaveManager.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

// ====================================
// Save Researcher and Challenges
// ====================================

bool SaveManager::SaveProgress(
    const Researcher& researcher,
    const std::vector<Challenge>& challenges,
    const std::string& filename)
{
    std::ofstream file(filename);

    if (!file.is_open())
    {
        std::cout << "\nError opening save file.\n";
        return false;
    }

    // Save researcher information.
    file << researcher.GetName() << '\n';
    file << researcher.GetLevel() << '\n';
    file << researcher.GetTotalXP() << '\n';
    file << researcher.GetAvailableXP() << '\n';

    // Save the number of challenges.
    file << challenges.size() << '\n';

    // Save each challenge's completion status.
    for (const Challenge& challenge : challenges)
    {
        file << challenge.IsCompleted() << '\n';
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
// Load Researcher and Challenges
// ====================================

bool SaveManager::LoadProgress(
    Researcher& researcher,
    std::vector<Challenge>& challenges,
    const std::string& filename)
{
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cout << "\nNo saved progress found.\n";
        return false;
    }

    std::string savedName;

    int savedLevel = 0;
    int savedTotalXP = 0;
    int savedAvailableXP = 0;

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

    // Read the number of saved challenges.
    std::size_t challengeCount = 0;

    if (!(file >> challengeCount) ||
        challengeCount != challenges.size())
    {
        std::cout << "\nInvalid challenge count.\n";
        return false;
    }

    // Read completion flags into temporary storage.
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

    // Validate researcher progress before changing it.
    if (!researcher.RestoreProgress(
        savedLevel,
        savedTotalXP,
        savedAvailableXP))
    {
        std::cout << "\nInvalid researcher progress.\n";
        return false;
    }

    // Restore challenge completion without awarding XP.
    for (std::size_t i = 0; i < challengeCount; i++)
    {
        challenges[i].RestoreCompletion(
            completedChallenges[i]);
    }

    std::cout << "\nProgress loaded successfully!\n";

    return true;
}