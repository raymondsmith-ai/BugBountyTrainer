#pragma once

#include <string>

class LearningModule
{
private:
    // Basic module information.
    std::string title;
    std::string description;
    std::string difficulty;

    // Progression information.
    int moduleLevel;
    int requiredLevel;

    // XP information.
    int xpReward;
    int unlockCost;

    // Module status.
    bool unlocked;
    bool completed;

public:
    // Constructor.
    LearningModule(
        const std::string& moduleTitle,
        const std::string& moduleDescription,
        const std::string& moduleDifficulty,
        int moduleNumber,
        int levelRequired,
        int reward,
        int cost,
        bool isUnlocked = false);

    // Getters.
    std::string GetTitle() const;
    std::string GetDescription() const;
    std::string GetDifficulty() const;

    int GetModuleLevel() const;
    int GetRequiredLevel() const;

    int GetXPReward() const;
    int GetUnlockCost() const;

    bool IsUnlocked() const;
    bool IsCompleted() const;

    // Changes the module state.
    void UnlockModule();
    void CompleteModule();

    // Displays module information.
    void DisplayModule() const;
};