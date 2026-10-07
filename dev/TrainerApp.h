#pragma once

#include <string>
#include <vector>

#include "Researcher.h"
#include "Challenge.h"

class TrainerApp
{
private:
    Researcher researcher;

    // Stores all training challenges.
    std::vector<Challenge> challenges;

    bool running;

    // Menu functions.
    void DisplayMenu() const;
    void HandleChoice(int choice);

    // Training functions.
    void DisplayChallenges() const;
    void StartTraining();

    // Input and usability functions.
    int GetValidatedChoice(int minimum, int maximum) const;
    void Pause() const;

public:
    // Constructor.
    TrainerApp(const std::string& researcherName);

    // Starts the application.
    void Run();
};