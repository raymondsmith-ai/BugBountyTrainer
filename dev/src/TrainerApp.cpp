#include "../include/TrainerApp.h"

#include <iostream>
#include <limits>

// Constructor.
TrainerApp::TrainerApp(
    const std::string& researcherName)
    : researcher(researcherName),
    running(true)
{
    // ====================================
    // Training Challenges
    // ====================================

    challenges.push_back(
        Challenge(
            "Authorization Basics",
            "Learn why permission is required before security testing.",
            "Authorization",
            "Easy",
            100,
            "Before testing a website for vulnerabilities, what should you verify first?",
            {
                "The website has a login page",
                "You have authorization to test the target",
                "The website uses HTTPS"
            },
            2
        )
    );

    challenges.push_back(
        Challenge(
            "Scope Basics",
            "Learn why bug bounty scope must be followed.",
            "Rules & Ethics",
            "Easy",
            150,
            "What should you do if a website or domain is not listed as an authorized target?",
            {
                "Test it anyway",
                "Do not test it unless you receive authorization",
                "Test only the login page"
            },
            2
        )
    );

    challenges.push_back(
        Challenge(
            "Input Validation Basics",
            "Learn why applications should validate user input.",
            "Input Validation",
            "Medium",
            200,
            "Why is input validation important?",
            {
                "It helps prevent unexpected or invalid data from being processed",
                "It makes every password stronger",
                "It removes the need for testing"
            },
            1
        )
    );

    // ====================================
    // Learning Path
    // ====================================

    // Level 0 starts unlocked.
    learningModules.push_back(
        LearningModule(
            "Rules, Ethics & Authorization",
            "Learn the legal and ethical rules of security testing.",
            "Beginner",
            0,
            1,
            100,
            0,
            true
        )
    );

    // Level 1.
    learningModules.push_back(
        LearningModule(
            "Computer Fundamentals",
            "Learn how computers, files, processes, users, and operating systems work.",
            "Beginner",
            1,
            1,
            125,
            50,
            false
        )
    );

    // Level 2.
    learningModules.push_back(
        LearningModule(
            "Linux Fundamentals",
            "Learn terminal navigation, commands, files, and permissions.",
            "Beginner",
            2,
            1,
            150,
            100,
            false
        )
    );

    // Level 3.
    learningModules.push_back(
        LearningModule(
            "Networking Fundamentals",
            "Learn IP addresses, ports, protocols, DNS, TCP, and UDP.",
            "Beginner",
            3,
            2,
            200,
            150,
            false
        )
    );

    // Level 4.
    learningModules.push_back(
        LearningModule(
            "Web Fundamentals",
            "Learn HTTP, requests, responses, headers, cookies, and web applications.",
            "Beginner",
            4,
            2,
            250,
            200,
            false
        )
    );

    // Level 5.
    learningModules.push_back(
        LearningModule(
            "Reconnaissance",
            "Learn how authorized security researchers discover and organize information about a target.",
            "Intermediate",
            5,
            3,
            300,
            300,
            false
        )
    );

    // Level 6.
    learningModules.push_back(
        LearningModule(
            "Web Vulnerability Fundamentals",
            "Learn common web security weaknesses and how they are identified in authorized environments.",
            "Intermediate",
            6,
            4,
            400,
            400,
            false
        )
    );

    // Level 7.
    learningModules.push_back(
        LearningModule(
            "Bug Bounty Methodology",
            "Learn how to organize research, validate findings, collect evidence, and prepare reports.",
            "Advanced",
            7,
            5,
            500,
            500,
            false
        )
    );
}

// ====================================
// Main Menu
// ====================================

void TrainerApp::DisplayMenu() const
{
    std::cout << "\n====================================\n";
    std::cout << "        BUG BOUNTY TRAINER\n";
    std::cout << "====================================\n";

    std::cout << "Researcher: "
        << researcher.GetName()
        << std::endl;

    std::cout << "Level: "
        << researcher.GetLevel()
        << std::endl;

    std::cout << "Total XP: "
        << researcher.GetTotalXP()
        << std::endl;

    std::cout << "Available XP: "
        << researcher.GetAvailableXP()
        << std::endl;

    std::cout << "====================================\n";

    std::cout << "1. View Researcher Profile\n";
    std::cout << "2. Learning Path\n";
    std::cout << "3. Start Training\n";
    std::cout << "4. View Challenges\n";
    std::cout << "5. Exit\n";

    std::cout << "====================================\n";
    std::cout << "Enter a number from 1 to 5: ";
}

// ====================================
// Input Validation
// ====================================

int TrainerApp::GetValidatedChoice(
    int minimum,
    int maximum) const
{
    int choice;

    while (true)
    {
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');

            std::cout << "\nInvalid input.\n";

            std::cout
                << "Please enter a number from "
                << minimum
                << " to "
                << maximum
                << ": ";

            continue;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');

        if (choice < minimum ||
            choice > maximum)
        {
            std::cout << "\nInvalid selection.\n";

            std::cout
                << "Please enter a number from "
                << minimum
                << " to "
                << maximum
                << ": ";

            continue;
        }

        return choice;
    }
}

// ====================================
// Learning Path Display
// ====================================

void TrainerApp::DisplayLearningPath() const
{
    std::cout << "\n====================================\n";
    std::cout << "           LEARNING PATH\n";
    std::cout << "====================================\n";

    std::cout << "Researcher Level: "
        << researcher.GetLevel()
        << std::endl;

    std::cout << "Total XP: "
        << researcher.GetTotalXP()
        << std::endl;

    std::cout << "Available XP: "
        << researcher.GetAvailableXP()
        << std::endl;

    std::cout << "====================================\n\n";

    for (int i = 0;
        i < static_cast<int>(learningModules.size());
        i++)
    {
        std::cout << i + 1 << ". ";

        if (learningModules[i].IsCompleted())
        {
            std::cout << "[COMPLETED] ";
        }
        else if (learningModules[i].IsUnlocked())
        {
            std::cout << "[AVAILABLE] ";
        }
        else
        {
            std::cout << "[LOCKED] ";
        }

        std::cout
            << "Level "
            << learningModules[i].GetModuleLevel()
            << " - "
            << learningModules[i].GetTitle()
            << std::endl;

        std::cout
            << "   Difficulty: "
            << learningModules[i].GetDifficulty()
            << std::endl;

        std::cout
            << "   XP Reward: "
            << learningModules[i].GetXPReward()
            << " XP"
            << std::endl;

        std::cout
            << "   Unlock Cost: "
            << learningModules[i].GetUnlockCost()
            << " XP"
            << std::endl;

        std::cout
            << "   Required Level: "
            << learningModules[i].GetRequiredLevel()
            << std::endl;

        std::cout << std::endl;
    }

    std::cout << "0. Return to Main Menu\n";
    std::cout << "====================================\n";
}

// ====================================
// Learning Path
// ====================================

void TrainerApp::OpenLearningPath()
{
    bool viewingLearningPath = true;

    while (viewingLearningPath)
    {
        DisplayLearningPath();

        std::cout << "Select a module: ";

        int choice = GetValidatedChoice(
            0,
            static_cast<int>(learningModules.size()));

        if (choice == 0)
        {
            viewingLearningPath = false;
            continue;
        }

        int moduleIndex = choice - 1;

        LearningModule* selectedModule =
            &learningModules[moduleIndex];

        // ====================================
        // Locked Module
        // ====================================

        if (!selectedModule->IsUnlocked())
        {
            std::cout << "\n====================================\n";
            std::cout << "           MODULE LOCKED\n";
            std::cout << "====================================\n";

            std::cout
                << "Module: "
                << selectedModule->GetTitle()
                << std::endl;

            std::cout
                << "Difficulty: "
                << selectedModule->GetDifficulty()
                << std::endl;

            std::cout
                << "Required Level: "
                << selectedModule->GetRequiredLevel()
                << std::endl;

            std::cout
                << "Unlock Cost: "
                << selectedModule->GetUnlockCost()
                << " XP"
                << std::endl;

            std::cout
                << "Available XP: "
                << researcher.GetAvailableXP()
                << std::endl;

            // ====================================
            // Prerequisite Check
            // ====================================

            if (moduleIndex > 0)
            {
                LearningModule* previousModule =
                    &learningModules[moduleIndex - 1];

                if (!previousModule->IsCompleted())
                {
                    std::cout << "\n====================================\n";
                    std::cout << "      PREREQUISITE NOT MET\n";
                    std::cout << "====================================\n";

                    std::cout
                        << "You must complete:\n";

                    std::cout
                        << "Level "
                        << previousModule->GetModuleLevel()
                        << " - "
                        << previousModule->GetTitle()
                        << std::endl;

                    std::cout
                        << "\nbefore unlocking:\n";

                    std::cout
                        << "Level "
                        << selectedModule->GetModuleLevel()
                        << " - "
                        << selectedModule->GetTitle()
                        << std::endl;

                    Pause();

                    continue;
                }
            }

            // ====================================
            // Researcher Level Check
            // ====================================

            if (researcher.GetLevel() <
                selectedModule->GetRequiredLevel())
            {
                std::cout << "\n====================================\n";
                std::cout << "          LEVEL TOO LOW\n";
                std::cout << "====================================\n";

                std::cout
                    << "Current Level: "
                    << researcher.GetLevel()
                    << std::endl;

                std::cout
                    << "Required Level: "
                    << selectedModule->GetRequiredLevel()
                    << std::endl;

                std::cout
                    << "\nComplete more training to level up.\n";

                Pause();

                continue;
            }

            // ====================================
            // XP Check
            // ====================================

            if (researcher.GetAvailableXP() <
                selectedModule->GetUnlockCost())
            {
                std::cout << "\n====================================\n";
                std::cout << "          NOT ENOUGH XP\n";
                std::cout << "====================================\n";

                std::cout
                    << "Available XP: "
                    << researcher.GetAvailableXP()
                    << std::endl;

                std::cout
                    << "Required XP: "
                    << selectedModule->GetUnlockCost()
                    << std::endl;

                std::cout
                    << "\nComplete more training to earn XP.\n";

                Pause();

                continue;
            }

            // ====================================
            // Purchase Module
            // ====================================

            std::cout << "\nPrerequisite completed!\n";
            std::cout << "You have enough XP.\n\n";

            std::cout << "1. Purchase Module\n";
            std::cout << "2. Cancel\n";
            std::cout << "Choice: ";

            int purchaseChoice =
                GetValidatedChoice(1, 2);

            if (purchaseChoice == 2)
            {
                std::cout
                    << "\nPurchase cancelled.\n";

                Pause();

                continue;
            }

            bool purchaseSuccessful =
                researcher.SpendXP(
                    selectedModule->GetUnlockCost());

            if (purchaseSuccessful)
            {
                selectedModule->UnlockModule();

                std::cout << "\n====================================\n";
                std::cout << "          MODULE UNLOCKED!\n";
                std::cout << "====================================\n";

                std::cout
                    << selectedModule->GetTitle()
                    << " is now available.\n";

                std::cout
                    << "\nTotal XP: "
                    << researcher.GetTotalXP()
                    << std::endl;

                std::cout
                    << "Available XP: "
                    << researcher.GetAvailableXP()
                    << std::endl;

                std::cout << "====================================\n";
            }

            Pause();

            continue;
        }

        // ====================================
        // Already Completed
        // ====================================

        if (selectedModule->IsCompleted())
        {
            selectedModule->DisplayModule();

            std::cout
                << "\nYou already completed this module.\n";

            std::cout
                << "It cannot award XP again.\n";

            Pause();

            continue;
        }

        // ====================================
        // Available Module
        // ====================================

        selectedModule->DisplayModule();

        std::cout << "\n====================================\n";
        std::cout << "           MODULE TRAINING\n";
        std::cout << "====================================\n";

        std::cout
            << "This module is available for training.\n\n";

        // Temporary completion option.
        // Real lessons will replace this later.
        std::cout << "1. Complete Module\n";
        std::cout << "2. Return to Learning Path\n";
        std::cout << "Choice: ";

        int moduleChoice =
            GetValidatedChoice(1, 2);

        if (moduleChoice == 2)
        {
            continue;
        }

        // ====================================
        // Complete Module
        // ====================================

        selectedModule->CompleteModule();

        researcher.AddXP(
            selectedModule->GetXPReward());

        std::cout << "\n====================================\n";
        std::cout << "          MODULE COMPLETED!\n";
        std::cout << "====================================\n";

        std::cout
            << selectedModule->GetTitle()
            << " completed!\n";

        std::cout
            << "\nYou earned "
            << selectedModule->GetXPReward()
            << " XP.\n";

        std::cout
            << "Total XP: "
            << researcher.GetTotalXP()
            << std::endl;

        std::cout
            << "Available XP: "
            << researcher.GetAvailableXP()
            << std::endl;

        if (moduleIndex + 1 <
            static_cast<int>(learningModules.size()))
        {
            std::cout << "\nNext Module:\n";

            std::cout
                << "Level "
                << learningModules[moduleIndex + 1]
                .GetModuleLevel()
                << " - "
                << learningModules[moduleIndex + 1]
                .GetTitle()
                << std::endl;

            std::cout
                << "You may now attempt to unlock it.\n";
        }
        else
        {
            std::cout
                << "\nYou completed the current learning path!\n";
        }

        std::cout << "====================================\n";

        Pause();
    }
}

// ====================================
// Challenge List
// ====================================

void TrainerApp::DisplayChallenges() const
{
    std::cout << "\n====================================\n";
    std::cout << "       TRAINING CHALLENGES\n";
    std::cout << "====================================\n";

    for (int i = 0;
        i < static_cast<int>(challenges.size());
        i++)
    {
        std::cout
            << i + 1
            << ". "
            << challenges[i].GetTitle()
            << std::endl;

        std::cout
            << "   Category: "
            << challenges[i].GetCategory()
            << std::endl;

        std::cout
            << "   Difficulty: "
            << challenges[i].GetDifficulty()
            << std::endl;

        std::cout
            << "   Reward: "
            << challenges[i].GetXPReward()
            << " XP"
            << std::endl;

        if (challenges[i].IsCompleted())
        {
            std::cout
                << "   Status: Completed\n";
        }
        else
        {
            std::cout
                << "   Status: Not Completed\n";
        }

        std::cout << std::endl;
    }

    std::cout << "====================================\n";
}

// ====================================
// Training Challenges
// ====================================

void TrainerApp::StartTraining()
{
    std::cout << "\n====================================\n";
    std::cout << "          START TRAINING\n";
    std::cout << "====================================\n";

    for (int i = 0;
        i < static_cast<int>(challenges.size());
        i++)
    {
        std::cout
            << i + 1
            << ". "
            << challenges[i].GetTitle()
            << " ["
            << challenges[i].GetDifficulty()
            << "]";

        if (challenges[i].IsCompleted())
        {
            std::cout << " - Completed";
        }

        std::cout << std::endl;
    }

    std::cout << "0. Return to Main Menu\n";
    std::cout << "====================================\n";

    std::cout << "Choose a challenge: ";

    int choice = GetValidatedChoice(
        0,
        static_cast<int>(challenges.size()));

    if (choice == 0)
    {
        return;
    }

    Challenge* selectedChallenge =
        &challenges[choice - 1];

    selectedChallenge->DisplayChallenge();

    if (selectedChallenge->IsCompleted())
    {
        std::cout
            << "\nYou already completed this challenge.\n";

        std::cout
            << "Choose another challenge to continue training.\n";

        return;
    }

    selectedChallenge->DisplayQuestion();

    std::cout << "\nEnter your answer: ";

    int answer = GetValidatedChoice(
        1,
        selectedChallenge->GetOptionCount());

    if (selectedChallenge->IsCorrectAnswer(answer))
    {
        int oldLevel =
            researcher.GetLevel();

        selectedChallenge->CompleteChallenge();

        researcher.AddXP(
            selectedChallenge->GetXPReward());

        std::cout << "\n====================================\n";
        std::cout << "        CHALLENGE COMPLETED!\n";
        std::cout << "====================================\n";

        std::cout << "Correct!\n";

        std::cout
            << "You earned "
            << selectedChallenge->GetXPReward()
            << " XP.\n";

        std::cout
            << "Total XP: "
            << researcher.GetTotalXP()
            << std::endl;

        std::cout
            << "Available XP: "
            << researcher.GetAvailableXP()
            << std::endl;

        if (researcher.GetLevel() >
            oldLevel)
        {
            std::cout << "\nLEVEL UP!\n";

            std::cout
                << "You are now Level "
                << researcher.GetLevel()
                << "!\n";
        }
    }
    else
    {
        std::cout << "\n====================================\n";
        std::cout << "          TRY AGAIN\n";
        std::cout << "====================================\n";

        std::cout
            << "That answer was not correct.\n";

        std::cout
            << "No XP was lost.\n";

        std::cout
            << "You can try this challenge again.\n";
    }
}

// ====================================
// Main Menu Choice Handling
// ====================================

void TrainerApp::HandleChoice(
    int choice)
{
    switch (choice)
    {
    case 1:
        researcher.DisplayProfile();
        break;

    case 2:
        OpenLearningPath();
        break;

    case 3:
        StartTraining();
        break;

    case 4:
        DisplayChallenges();
        break;

    case 5:
        running = false;

        std::cout
            << "\nThank you for using Bug Bounty Trainer!\n";

        std::cout
            << "Keep learning and test responsibly.\n";

        break;
    }
}

// ====================================
// Pause
// ====================================

void TrainerApp::Pause() const
{
    std::cout
        << "\nPress Enter to continue...";

    std::cin.get();
}

// ====================================
// Run Application
// ====================================

void TrainerApp::Run()
{
    while (running)
    {
        DisplayMenu();

        int choice =
            GetValidatedChoice(1, 5);

        HandleChoice(choice);

        // Learning Path already handles
        // its own pause screens.
        if (running &&
            choice != 2)
        {
            Pause();
        }
    }
}