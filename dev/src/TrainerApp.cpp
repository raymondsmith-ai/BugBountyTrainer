#include "../include/TrainerApp.h"

#include <iostream>
#include <limits>

// ====================================
// Constructor
// ====================================

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

    learningModules.push_back(
        LearningModule(
            "Reconnaissance",
            "Learn how authorized researchers discover and organize information about a target.",
            "Intermediate",
            5,
            3,
            300,
            300,
            false
        )
    );

    learningModules.push_back(
        LearningModule(
            "Web Vulnerability Fundamentals",
            "Learn common web weaknesses inside authorized training environments.",
            "Intermediate",
            6,
            4,
            400,
            400,
            false
        )
    );

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

    // ====================================
    // Hands-On Labs
    // ====================================

    Lab terminalLab(
        "Terminal Investigation",
        "Practice investigating a simulated BugBountyTrainer workstation using terminal commands.",
        "Beginner",
        150,
        true
    );

    terminalLab.AddObjective(
        "Identify the current user.");

    terminalLab.AddObjective(
        "List the files in the training directory.");

    terminalLab.AddObjective(
        "Read the training.txt file.");

    terminalLab.AddObjective(
        "Recover the validation code.");

    labs.push_back(terminalLab);

    // Future lab.
    Lab networkLab(
        "Network Discovery",
        "Practice identifying services inside an isolated training network.",
        "Beginner",
        200,
        false
    );

    networkLab.AddObjective(
        "Identify the training target.");

    networkLab.AddObjective(
        "Discover the exposed service.");

    networkLab.AddObjective(
        "Identify the service type.");

    labs.push_back(networkLab);
}

// ====================================
// Main Menu
// ====================================

void TrainerApp::DisplayMenu() const
{
    std::cout << "\n====================================\n";
    std::cout << "        BUG BOUNTY TRAINER\n";
    std::cout << "====================================\n";

    std::cout
        << "Researcher: "
        << researcher.GetName()
        << std::endl;

    std::cout
        << "Level: "
        << researcher.GetLevel()
        << std::endl;

    std::cout
        << "Total XP: "
        << researcher.GetTotalXP()
        << std::endl;

    std::cout
        << "Available XP: "
        << researcher.GetAvailableXP()
        << std::endl;

    std::cout << "====================================\n";

    std::cout << "1. View Researcher Profile\n";
    std::cout << "2. Learning Path\n";
    std::cout << "3. Hands-On Labs\n";
    std::cout << "4. Start Training\n";
    std::cout << "5. View Challenges\n";
    std::cout << "6. Exit\n";

    std::cout << "====================================\n";
    std::cout << "Enter a number from 1 to 6: ";
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

    std::cout
        << "Researcher Level: "
        << researcher.GetLevel()
        << std::endl;

    std::cout
        << "Total XP: "
        << researcher.GetTotalXP()
        << std::endl;

    std::cout
        << "Available XP: "
        << researcher.GetAvailableXP()
        << std::endl;

    std::cout << "====================================\n\n";

    for (int i = 0;
        i < static_cast<int>(
            learningModules.size());
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
            static_cast<int>(
                learningModules.size()));

        if (choice == 0)
        {
            viewingLearningPath = false;
            continue;
        }

        int moduleIndex =
            choice - 1;

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

            // Previous module must be complete.
            if (moduleIndex > 0)
            {
                LearningModule* previousModule =
                    &learningModules[
                        moduleIndex - 1];

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

                    Pause();

                    continue;
                }
            }

            // Researcher level check.
            if (researcher.GetLevel() <
                selectedModule->GetRequiredLevel())
            {
                std::cout << "\nYour researcher level is too low.\n";

                std::cout
                    << "Required Level: "
                    << selectedModule->GetRequiredLevel()
                    << std::endl;

                Pause();

                continue;
            }

            // XP check.
            if (researcher.GetAvailableXP() <
                selectedModule->GetUnlockCost())
            {
                std::cout << "\nNot enough available XP.\n";

                Pause();

                continue;
            }

            std::cout << "\nPrerequisites completed.\n\n";
            std::cout << "1. Purchase Module\n";
            std::cout << "2. Cancel\n";
            std::cout << "Choice: ";

            int purchaseChoice =
                GetValidatedChoice(1, 2);

            if (purchaseChoice == 2)
            {
                continue;
            }

            if (researcher.SpendXP(
                selectedModule->GetUnlockCost()))
            {
                selectedModule->UnlockModule();

                std::cout << "\n====================================\n";
                std::cout << "          MODULE UNLOCKED!\n";
                std::cout << "====================================\n";

                std::cout
                    << selectedModule->GetTitle()
                    << " is now available.\n";

                std::cout
                    << "Available XP: "
                    << researcher.GetAvailableXP()
                    << std::endl;

                Pause();
            }

            continue;
        }

        // ====================================
        // Completed Module
        // ====================================

        if (selectedModule->IsCompleted())
        {
            selectedModule->DisplayModule();

            std::cout
                << "\nThis module has already been completed.\n";

            Pause();

            continue;
        }

        // ====================================
        // Temporary Module Screen
        // ====================================

        selectedModule->DisplayModule();

        std::cout << "\n====================================\n";
        std::cout << "           MODULE TRAINING\n";
        std::cout << "====================================\n";

        std::cout
            << "Module completion will soon require "
            << "its assigned hands-on lab.\n\n";

        std::cout
            << "The temporary Complete Module option "
            << "will be removed after lab integration.\n";

        Pause();
    }
}

// ====================================
// Hands-On Labs Display
// ====================================

void TrainerApp::DisplayLabs() const
{
    std::cout << "\n====================================\n";
    std::cout << "           HANDS-ON LABS\n";
    std::cout << "====================================\n";

    for (int i = 0;
        i < static_cast<int>(
            labs.size());
        i++)
    {
        std::cout
            << i + 1
            << ". ";

        if (labs[i].IsCompleted())
        {
            std::cout << "[COMPLETED] ";
        }
        else if (labs[i].IsUnlocked())
        {
            std::cout << "[AVAILABLE] ";
        }
        else
        {
            std::cout << "[LOCKED] ";
        }

        std::cout
            << labs[i].GetTitle()
            << std::endl;

        std::cout
            << "   Difficulty: "
            << labs[i].GetDifficulty()
            << std::endl;

        std::cout
            << "   Reward: "
            << labs[i].GetXPReward()
            << " XP"
            << std::endl;

        std::cout << std::endl;
    }

    std::cout << "0. Return to Main Menu\n";
    std::cout << "====================================\n";
}

// ====================================
// Hands-On Labs Menu
// ====================================

void TrainerApp::OpenHandsOnLabs()
{
    bool viewingLabs = true;

    while (viewingLabs)
    {
        DisplayLabs();

        std::cout << "Select a lab: ";

        int choice = GetValidatedChoice(
            0,
            static_cast<int>(
                labs.size()));

        if (choice == 0)
        {
            viewingLabs = false;
            continue;
        }

        Lab* selectedLab =
            &labs[choice - 1];

        if (!selectedLab->IsUnlocked())
        {
            std::cout << "\n====================================\n";
            std::cout << "             LAB LOCKED\n";
            std::cout << "====================================\n";

            std::cout
                << selectedLab->GetTitle()
                << " is not available yet.\n";

            std::cout
                << "Complete earlier training first.\n";

            Pause();

            continue;
        }

        if (selectedLab->IsCompleted())
        {
            selectedLab->DisplayLab();
            selectedLab->DisplayObjectives();

            std::cout
                << "\nYou already completed this lab.\n";

            std::cout
                << "No additional XP will be awarded.\n";

            Pause();

            continue;
        }

        // First simulated lab.
        if (choice == 1)
        {
            RunTerminalInvestigationLab(
                *selectedLab);
        }
    }
}

// ====================================
// Terminal Investigation Lab
// ====================================

void TrainerApp::RunTerminalInvestigationLab(
    Lab& lab)
{
    bool labRunning = true;

    std::string command;

    lab.DisplayLab();

    std::cout << "\n====================================\n";
    std::cout << "        SAFE LAB ENVIRONMENT\n";
    std::cout << "====================================\n";

    std::cout
        << "You are inside a simulated "
        << "BugBountyTrainer workstation.\n";

    std::cout
        << "Commands entered here do NOT run "
        << "against your real computer.\n\n";

    std::cout
        << "Your goal is to investigate the "
        << "training directory.\n";

    std::cout << "\nUseful command:\n";
    std::cout << "help\n";

    std::cout << "====================================\n";

    while (labRunning)
    {
        std::cout << "\nBBT-LAB> ";

        std::getline(
            std::cin,
            command);

        // ====================================
        // Help
        // ====================================

        if (command == "help")
        {
            std::cout << "\nAvailable simulated commands:\n";
            std::cout << "whoami\n";
            std::cout << "dir\n";
            std::cout << "type <filename>\n";
            std::cout << "status\n";
            std::cout << "exit\n";
        }

        // ====================================
        // whoami
        // ====================================

        else if (command == "whoami")
        {
            std::cout
                << "bbt-training\\researcher\n";

            if (!lab.IsObjectiveCompleted(1))
            {
                lab.CompleteObjective(1);

                std::cout
                    << "[OBJECTIVE COMPLETE] "
                    << "Current user identified.\n";
            }
        }

        // ====================================
        // dir
        // ====================================

        else if (command == "dir")
        {
            std::cout << "\nDirectory of C:\\BBT-Lab\n\n";

            std::cout
                << "10/09/2026  06:00 AM    "
                << "<DIR>          logs\n";

            std::cout
                << "10/09/2026  06:00 AM             "
                << "94 training.txt\n";

            std::cout
                << "10/09/2026  06:00 AM             "
                << "38 notes.txt\n";

            if (!lab.IsObjectiveCompleted(2))
            {
                lab.CompleteObjective(2);

                std::cout
                    << "\n[OBJECTIVE COMPLETE] "
                    << "Training directory inspected.\n";
            }
        }

        // ====================================
        // Read training.txt
        // ====================================

        else if (command == "type training.txt")
        {
            // Require directory investigation first.
            if (!lab.IsObjectiveCompleted(2))
            {
                std::cout
                    << "Investigate the directory first.\n";

                continue;
            }

            std::cout << "\nBUG BOUNTY TRAINER\n";
            std::cout << "Authorized Training File\n";
            std::cout << "Validation Code: BBT-ALPHA-101\n";

            if (!lab.IsObjectiveCompleted(3))
            {
                lab.CompleteObjective(3);

                std::cout
                    << "\n[OBJECTIVE COMPLETE] "
                    << "training.txt inspected.\n";
            }

            if (!lab.IsObjectiveCompleted(4))
            {
                lab.CompleteObjective(4);

                std::cout
                    << "[OBJECTIVE COMPLETE] "
                    << "Validation code recovered.\n";
            }
        }

        // Optional notes file.
        else if (command == "type notes.txt")
        {
            std::cout
                << "Hint: Inspect training.txt.\n";
        }

        // ====================================
        // Status
        // ====================================

        else if (command == "status")
        {
            lab.DisplayObjectives();
        }

        // ====================================
        // Exit
        // ====================================

        else if (command == "exit")
        {
            labRunning = false;
        }

        // Blank command.
        else if (command.empty())
        {
            continue;
        }

        // Unknown command.
        else
        {
            std::cout
                << "'"
                << command
                << "' is not a recognized "
                << "lab command.\n";

            std::cout
                << "Type help to view available commands.\n";
        }

        // ====================================
        // Automatic Lab Validation
        // ====================================

        if (lab.AreAllObjectivesCompleted() &&
            !lab.IsCompleted())
        {
            bool completed =
                lab.CompleteLab();

            if (completed)
            {
                researcher.AddXP(
                    lab.GetXPReward());

                std::cout << "\n====================================\n";
                std::cout << "            LAB COMPLETE!\n";
                std::cout << "====================================\n";

                std::cout
                    << lab.GetTitle()
                    << " completed successfully.\n";

                std::cout
                    << "\nAll required objectives "
                    << "were validated.\n";

                std::cout
                    << "\nXP Earned: "
                    << lab.GetXPReward()
                    << std::endl;

                std::cout
                    << "Total XP: "
                    << researcher.GetTotalXP()
                    << std::endl;

                std::cout
                    << "Available XP: "
                    << researcher.GetAvailableXP()
                    << std::endl;

                std::cout << "====================================\n";

                labRunning = false;
            }
        }
    }

    if (!lab.IsCompleted())
    {
        std::cout
            << "\nLab exited before completion.\n";

        std::cout
            << "Your completed objectives remain "
            << "available during this session.\n";
    }

    Pause();
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
        i < static_cast<int>(
            challenges.size());
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
        i < static_cast<int>(
            challenges.size());
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
        static_cast<int>(
            challenges.size()));

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

        return;
    }

    selectedChallenge->DisplayQuestion();

    std::cout << "\nEnter your answer: ";

    int answer =
        GetValidatedChoice(
            1,
            selectedChallenge->GetOptionCount());

    if (selectedChallenge->IsCorrectAnswer(
        answer))
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
        OpenHandsOnLabs();
        break;

    case 4:
        StartTraining();
        break;

    case 5:
        DisplayChallenges();
        break;

    case 6:
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
            GetValidatedChoice(1, 6);

        HandleChoice(choice);

        // Learning Path and Lab menus
        // handle their own pauses.
        if (running &&
            choice != 2 &&
            choice != 3)
        {
            Pause();
        }
    }
}