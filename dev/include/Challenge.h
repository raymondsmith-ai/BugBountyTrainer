#pragma once

#include <string>
#include <vector>

class Challenge
{
private:
    std::string title;
    std::string description;
    std::string difficulty;

    int xpReward;
    bool completed;

    std::string question;
    std::vector<std::string> answerOptions;
    int correctAnswer;

public:
    // Constructor
    Challenge(
        const std::string& challengeTitle,
        const std::string& challengeDescription,
        const std::string& challengeDifficulty,
        int reward,
        const std::string& challengeQuestion,
        const std::vector<std::string>& options,
        int answer);

    // Getters
    std::string GetTitle() const;
    std::string GetDescription() const;
    std::string GetDifficulty() const;

    int GetXPReward() const;
    int GetOptionCount() const;

    bool IsCompleted() const;

    // Challenge functions
    void DisplayChallenge() const;
    void DisplayQuestion() const;

    bool IsCorrectAnswer(int answer) const;

    void CompleteChallenge();
};