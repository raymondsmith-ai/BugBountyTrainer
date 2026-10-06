#include "../include/Challenge.h"

#include <iostream>

// Constructor
Challenge::Challenge(
    const std::string& challengeTitle,
    const std::string& challengeDescription,
    const std::string& challengeDifficulty,
    int reward,
    const std::string& challengeQuestion,
    const std::vector<std::string>& options,
    int answer)
{
    title = challengeTitle;
    description = challengeDescription;
    difficulty = challengeDifficulty;

    xpReward = reward;
    completed = false;

    question = challengeQuestion;
    answerOptions = options;
    correctAnswer = answer;
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

// Returns the difficulty
std::string Challenge::GetDifficulty() const
{
    return difficulty;
}

// Returns the XP reward
int Challenge::GetXPReward() const
{
    return xpReward;
}

// Returns the number of answer choices
int Challenge::GetOptionCount() const
{
    return static_cast<int>(answerOptions.size());
}

// Returns whether the challenge has been completed
bool Challenge::IsCompleted() const
{
    return completed;
}

// Displays general challenge information
void Challenge::DisplayChallenge() const
{
    std::cout << "\n====================================\n";
    std::cout << "             CHALLENGE\n";
    std::cout << "====================================\n";

    std::cout << "Title:       " << title << std::endl;
    std::cout << "Difficulty:  " << difficulty << std::endl;
    std::cout << "XP Reward:   " << xpReward << std::endl;
    std::cout << "Description: " << description << std::endl;

    if (completed)
    {
        std::cout << "Status:      Completed\n";
    }
    else
    {
        std::cout << "Status:      Not Completed\n";
    }

    std::cout << "====================================\n";
}

// Displays the question and answer choices
void Challenge::DisplayQuestion() const
{
    std::cout << "\nQuestion:\n";
    std::cout << question << "\n\n";

    for (int i = 0; i < static_cast<int>(answerOptions.size()); i++)
    {
        std::cout << i + 1 << ". "
            << answerOptions[i]
            << std::endl;
    }
}

// Checks the user's answer
bool Challenge::IsCorrectAnswer(int answer) const
{
    return answer == correctAnswer;
}

// Marks the challenge as completed
void Challenge::CompleteChallenge()
{
    completed = true;
}