#pragma once

#include <string>
#include <vector>

#include "Researcher.h"
#include "Challenge.h"
#include "LearningModule.h"
#include "Lab.h"

class TrainerApp
{
private:
    Researcher researcher;

    // Stores training challenges.
    std::vector<Challenge> challenges;

    // Stores learning modules.
    std::vector<LearningModule> learningModules;

    // Stores hands-on labs.
    std::vector<Lab> labs;

    bool running;

    // Main menu functions.
    void DisplayMenu() const;
    void HandleChoice(int choice);

    // Learning path functions.
    void DisplayLearningPath() const;
    void OpenLearningPath();

    // Hands-on lab functions.
    void DisplayLabs() const;
    void OpenHandsOnLabs();

    void RunTerminalInvestigationLab(
        Lab& lab);

    // Training functions.
    void DisplayChallenges() const;
    void StartTraining();

    // Input and usability functions.
    int GetValidatedChoice(
        int minimum,
        int maximum) const;

    void Pause() const;

public:
    TrainerApp(
        const std::string& researcherName);

    void Run();
};