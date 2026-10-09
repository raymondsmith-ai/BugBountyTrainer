#include "../include/Lab.h"

#include <iostream>

// Constructor.
Lab::Lab(
    const std::string& labTitle,
    const std::string& labDescription,
    const std::string& labDifficulty,
    int reward,
    bool isUnlocked)
{
    title = labTitle;
    description = labDescription;
    difficulty = labDifficulty;

    xpReward = reward;

    unlocked = isUnlocked;
    completed = false;
}

// Returns the lab title.
std::string Lab::GetTitle() const
{
    return title;
}

// Returns the lab description.
std::string Lab::GetDescription() const
{
    return description;
}

// Returns the difficulty.
std::string Lab::GetDifficulty() const
{
    return difficulty;
}

// Returns the XP reward.
int Lab::GetXPReward() const
{
    return xpReward;
}

// Returns the number of objectives.
int Lab::GetObjectiveCount() const
{
    return static_cast<int>(
        objectives.size());
}

// Returns whether the lab is unlocked.
bool Lab::IsUnlocked() const
{
    return unlocked;
}

// Returns whether the lab is complete.
bool Lab::IsCompleted() const
{
    return completed;
}

// Adds a required objective.
void Lab::AddObjective(
    const std::string& objective)
{
    objectives.push_back(objective);

    // Every new objective starts incomplete.
    objectiveCompleted.push_back(false);
}

// Unlocks the lab.
void Lab::UnlockLab()
{
    unlocked = true;
}

// Marks one objective complete.
bool Lab::CompleteObjective(
    int objectiveNumber)
{
    int index =
        objectiveNumber - 1;

    if (index < 0 ||
        index >= static_cast<int>(
            objectives.size()))
    {
        return false;
    }

    // Do not complete the same objective twice.
    if (objectiveCompleted[index])
    {
        return false;
    }

    objectiveCompleted[index] = true;

    return true;
}

// Checks one objective.
bool Lab::IsObjectiveCompleted(
    int objectiveNumber) const
{
    int index =
        objectiveNumber - 1;

    if (index < 0 ||
        index >= static_cast<int>(
            objectiveCompleted.size()))
    {
        return false;
    }

    return objectiveCompleted[index];
}

// Checks whether every required objective is complete.
bool Lab::AreAllObjectivesCompleted() const
{
    if (objectives.empty())
    {
        return false;
    }

    for (int i = 0;
        i < static_cast<int>(
            objectiveCompleted.size());
        i++)
    {
        if (!objectiveCompleted[i])
        {
            return false;
        }
    }

    return true;
}

// Attempts to complete the lab.
bool Lab::CompleteLab()
{
    if (!unlocked)
    {
        return false;
    }

    if (!AreAllObjectivesCompleted())
    {
        return false;
    }

    completed = true;

    return true;
}

// Displays basic lab information.
void Lab::DisplayLab() const
{
    std::cout << "\n====================================\n";
    std::cout << "          HANDS-ON LAB\n";
    std::cout << "====================================\n";

    std::cout
        << "Title:       "
        << title
        << std::endl;

    std::cout
        << "Difficulty:  "
        << difficulty
        << std::endl;

    std::cout
        << "Description: "
        << description
        << std::endl;

    std::cout
        << "XP Reward:   "
        << xpReward
        << " XP"
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

// Displays the required objectives.
void Lab::DisplayObjectives() const
{
    std::cout << "\n====================================\n";
    std::cout << "          LAB OBJECTIVES\n";
    std::cout << "====================================\n";

    if (objectives.empty())
    {
        std::cout
            << "No objectives have been added.\n";

        std::cout << "====================================\n";

        return;
    }

    for (int i = 0;
        i < static_cast<int>(
            objectives.size());
        i++)
    {
        if (objectiveCompleted[i])
        {
            std::cout << "[X] ";
        }
        else
        {
            std::cout << "[ ] ";
        }

        std::cout
            << i + 1
            << ". "
            << objectives[i]
            << std::endl;
    }

    std::cout << "====================================\n";
}