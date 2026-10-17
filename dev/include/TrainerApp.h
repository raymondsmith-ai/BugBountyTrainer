#pragma once

#include <string>
#include <vector>

#include "Researcher.h"
#include "Challenge.h"
#include "LearningModule.h"
#include "Lab.h"
#include "SQLFundamentals.h"
#include "SQLInjection.h"

class TrainerApp
{
private:
    Researcher researcher;

    std::vector<Challenge> challenges;
    std::vector<LearningModule> learningModules;
    std::vector<Lab> labs;

    SQLFundamentals sqlFundamentals;
    SQLInjection sqlInjection;

    bool running;

    // Startup menu.
    void DisplayStartupMenu() const;
    void OpenOptions();
    bool StartSession();

    // Saved-user management.
    bool SelectSavedUser();
    void DeleteSavedUser();

    // Main menu.
    void DisplayMenu() const;
    void HandleChoice(int choice);

    // Learning path.
    void DisplayLearningPath() const;
    void OpenLearningPath();

    // Hands-on labs.
    void DisplayLabs() const;
    void OpenHandsOnLabs();
    void RunTerminalInvestigationLab(Lab& lab);

    // Training challenges.
    void DisplayChallenges() const;
    void StartTraining();

    // Vulnerability categories.
    std::vector<std::string> GetCategories() const;
    void DisplayCategories() const;
    void BrowseCategories();

    void DisplayChallengesByCategory(
        const std::string& selectedCategory) const;

    // Save and load current researcher progress.
    void SaveProgress();
    void LoadProgress();

    // Input and utility functions.
    int GetValidatedChoice(
        int minimum,
        int maximum) const;

    void Pause() const;

public:
    explicit TrainerApp(const std::string& researcherName);

    void Run();
};
