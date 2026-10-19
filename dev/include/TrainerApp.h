#pragma once

#include <string>
#include <vector>

#include "Researcher.h"
#include "Challenge.h"
#include "LearningModule.h"
#include "Lab.h"
#include "SQLFundamentals.h"
#include "SQLInjection.h"
#include "SQLAcademy.h"

// ====================================
// BugBountyTrainer Application
// ====================================

class TrainerApp
{
private:
    // ====================================
    // Researcher Profile
    // ====================================

    Researcher researcher;

    // ====================================
    // Training Data
    // ====================================

    std::vector<Challenge> challenges;
    std::vector<LearningModule> learningModules;
    std::vector<Lab> labs;

    // ====================================
    // SQL Training Systems
    // ====================================

    // Stage 1: SQL Fundamentals
    SQLFundamentals sqlFundamentals;

    // Stage 2: SQL Injection Training
    SQLInjection sqlInjection;

    // Complete 13-module SQL Academy
    SQLAcademy sqlAcademy;

    // ====================================
    // Application State
    // ====================================

    bool running;

    // ====================================
    // Startup Menu
    // ====================================

    void DisplayStartupMenu() const;
    void OpenOptions();
    bool StartSession();

    // ====================================
    // Saved User Management
    // ====================================

    bool SelectSavedUser();
    void DeleteSavedUser();

    // ====================================
    // Main Menu
    // ====================================

    void DisplayMenu() const;
    void HandleChoice(int choice);

    // ====================================
    // Docker SQL Injection Labs
    // ====================================

    void OpenDockerLabs();

    // ====================================
    // Learning Path
    // ====================================

    void DisplayLearningPath() const;
    void OpenLearningPath();

    // ====================================
    // Hands-On Labs
    // ====================================

    void DisplayLabs() const;
    void OpenHandsOnLabs();
    void RunTerminalInvestigationLab(Lab& lab);

    // ====================================
    // Training Challenges
    // ====================================

    void DisplayChallenges() const;
    void StartTraining();

    // ====================================
    // Vulnerability Categories
    // ====================================

    std::vector<std::string> GetCategories() const;

    void DisplayCategories() const;
    void BrowseCategories();

    void DisplayChallengesByCategory(
        const std::string& selectedCategory) const;

    // ====================================
    // Save and Load Progress
    // ====================================

    void SaveProgress();
    void LoadProgress();

    // ====================================
    // Input Validation and Utilities
    // ====================================

    int GetValidatedChoice(
        int minimum,
        int maximum) const;

    void Pause() const;

public:
    // ====================================
    // Constructor
    // ====================================

    explicit TrainerApp(
        const std::string& researcherName);

    // ====================================
    // Application Main Loop
    // ====================================

    void Run();
};