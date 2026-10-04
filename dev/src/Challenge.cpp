#include "../include/Challenge.h"
#include <iostream>

// Constructor
Challenge::Challenge(
    const std::string& challengeTitle,
    const std::string& challengeDescription,
    int reward)
{
    title = challengeTitle;
    description = challengeDescription;
    xpReward = reward;
    completed = false;
}

// Returns the challenge title
std::string Challenge::GetTitle() const
{
    return title;
}

// Returns the challenge description
std::string Challenge::GetDescription() const
{
    return description;
}

// Returns the XP reward
int Challenge::GetXPReward() const
{
    return xpReward;
}

// Returns whether the challenge has been completed
bool Challenge::IsCompleted() const
{
    return completed;
}

// Displays the challenge information
void Challenge::DisplayChallenge() const
{
    std::cout << "\n--- Challenge ---\n";
    std::cout << "Title: " << title << std::endl;
    std::cout << "Description: " << description << std::endl;
    std::cout << "XP Reward: " << xpReward << std::endl;

    if (completed)
    {
        std::cout << "Status: Completed" << std::endl;
    }
    else
    {
        std::cout << "Status: Not Completed" << std::endl;
    }
}

// Marks the challenge as completed
void Challenge::CompleteChallenge()
{
    completed = true;
}