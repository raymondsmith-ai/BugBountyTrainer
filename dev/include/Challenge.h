#pragma once

#include <string>

class Challenge
{
private:
    std::string title;
    std::string description;
    int xpReward;
    bool completed;

public:
    // Constructor
    Challenge(
        const std::string& challengeTitle,
        const std::string& challengeDescription,
        int reward);

    // Getters
    std::string GetTitle() const;
    std::string GetDescription() const;
    int GetXPReward() const;
    bool IsCompleted() const;

    // Displays challenge information
    void DisplayChallenge() const;

    // Marks the challenge as completed
    void CompleteChallenge();
};