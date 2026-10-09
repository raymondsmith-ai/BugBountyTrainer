#pragma once

#include <string>
#include <vector>

#include "Researcher.h"
#include "Challenge.h"
#include "LearningModule.h"

class TrainerApp
{
private:
    Researcher researcher;

    // Stores all training challenges.
    std::vector<Challenge> challenges;

    // Stores learning modules in order from beginner to advanced.
    std::vector<LearningModule> learningModules;

    bool running;

    // Main menu functions.
    void DisplayMenu() const;
    void HandleChoice(int choice);

    // Learning path functions.
    void DisplayLearningPath() const;
    void OpenLearningPath();

    // Training functions.
    void DisplayChallenges() const;
    void StartTraining();

    // Usability functions.
    int GetValidatedChoice(int minimum, int maximum) const;
    void Pause() const;

public:
    TrainerApp(const std::string& researcherName);

    void Run();
};