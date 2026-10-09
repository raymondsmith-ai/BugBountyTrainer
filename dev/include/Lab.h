#pragma once

#include <string>
#include <vector>

class Lab
{
private:
    std::string title;
    std::string description;
    std::string difficulty;

    int xpReward;

    bool unlocked;
    bool completed;

    // The tasks required to finish the lab.
    std::vector<std::string> objectives;

    // Matches each objective with its completion state.
    std::vector<bool> objectiveCompleted;

public:
    Lab(
        const std::string& labTitle,
        const std::string& labDescription,
        const std::string& labDifficulty,
        int reward,
        bool isUnlocked = false);

    // Getters.
    std::string GetTitle() const;
    std::string GetDescription() const;
    std::string GetDifficulty() const;

    int GetXPReward() const;
    int GetObjectiveCount() const;

    bool IsUnlocked() const;
    bool IsCompleted() const;

    // Lab setup.
    void AddObjective(
        const std::string& objective);

    // Progression.
    void UnlockLab();

    bool CompleteObjective(
        int objectiveNumber);

    bool IsObjectiveCompleted(
        int objectiveNumber) const;

    bool AreAllObjectivesCompleted() const;

    bool CompleteLab();

    // Display.
    void DisplayLab() const;
    void DisplayObjectives() const;
};
