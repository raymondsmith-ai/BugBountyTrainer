#include "../include/LearningModule.h"

#include <iostream>

LearningModule::LearningModule(
    const std::string& moduleTitle,
    const std::string& moduleDescription,
    const std::string& moduleDifficulty,
    int moduleNumber,
    int levelRequired,
    int reward,
    int cost,
    bool isUnlocked)
{
    title = moduleTitle;
    description = moduleDescription;
    difficulty = moduleDifficulty;

    moduleLevel = moduleNumber;
    requiredLevel = levelRequired;

    xpReward = reward;
    unlockCost = cost;

    unlocked = isUnlocked;
    completed = false;
}

std::string LearningModule::GetTitle() const
{
    return title;
}

std::string LearningModule::GetDescription() const
{
    return description;
}

std::string LearningModule::GetDifficulty() const
{
    return difficulty;
}

int LearningModule::GetModuleLevel() const
{
    return moduleLevel;
}

int LearningModule::GetRequiredLevel() const
{
    return requiredLevel;
}

int LearningModule::GetXPReward() const
{
    return xpReward;
}

int LearningModule::GetUnlockCost() const
{
    return unlockCost;
}

bool LearningModule::IsUnlocked() const
{
    return unlocked;
}

bool LearningModule::IsCompleted() const
{
    return completed;
}

void LearningModule::UnlockModule()
{
    unlocked = true;
}

void LearningModule::CompleteModule()
{
    if (unlocked)
    {
        completed = true;
    }
}

void LearningModule::DisplayModule() const
{
    std::cout << "\n====================================\n";
    std::cout << "          LEARNING MODULE\n";
    std::cout << "====================================\n";

    std::cout << "Level:       "
        << moduleLevel
        << std::endl;

    std::cout << "Title:       "
        << title
        << std::endl;

    std::cout << "Difficulty:  "
        << difficulty
        << std::endl;

    std::cout << "Description: "
        << description
        << std::endl;

    std::cout << "XP Reward:   "
        << xpReward
        << " XP"
        << std::endl;

    std::cout << "Unlock Cost: "
        << unlockCost
        << " XP"
        << std::endl;

    std::cout << "Required Researcher Level: "
        << requiredLevel
        << std::endl;

    std::cout << "Status:      ";

    if (completed)
    {
        std::cout << "Completed";
    }
    else if (unlocked)
    {
        std::cout << "Available";
    }
    else
    {
        std::cout << "Locked";
    }

    std::cout << std::endl;

    std::cout << "====================================\n";
}