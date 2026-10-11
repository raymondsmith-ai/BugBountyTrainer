#include "../include/TrainerApp.h"

#include <iostream>
#include <limits>

// ====================================
// Constructor
// ====================================

TrainerApp::TrainerApp(const std::string& researcherName)
    : researcher(researcherName), running(true)
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
    // Learning Modules
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

    terminalLab.AddObjective("Identify the current user.");
    terminalLab.AddObjective("List the files in the training directory.");
    terminalLab.AddObjective("Read the training.txt file.");
    terminalLab.AddObjective("Recover the validation code.");

    labs.push_back(terminalLab);

    // Future training lab.
    Lab networkLab(
        "Network Discovery",
        "Practice identifying services inside an isolated training network.",
        "Beginner",
        200,
        false
    );

    networkLab.AddObjective("Identify the training target.");
    networkLab.AddObjective("Discover the exposed service.");
    networkLab.AddObjective("Identify the service type.");

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

    std::cout << "Researcher: "
        << researcher.GetName() << std::endl;

    std::cout << "Level: "
        << researcher.GetLevel() << std::endl;

    std::cout << "Total XP: "
        << researcher.GetTotalXP() << std::endl;

    std::cout << "Available XP: "
        << researcher.GetAvailableXP() << std::endl;

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

int TrainerApp::GetValidatedChoice(int minimum, int maximum) const
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
        }
        else
        {
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');

            if (choice >= minimum && choice <= maximum)
            {
                return choice;
            }

            std::cout << "\nInvalid selection.\n";
        }

        std::cout << "Please enter a number from "
            << minimum << " to "
            << maximum << ": ";
    }
}

// ====================================
// Display Learning Path
// ====================================

void TrainerApp::DisplayLearningPath() const
{
    std::cout << "\n====================================\n";
    std::cout << "           LEARNING PATH\n";
    std::cout << "====================================\n";

    std::cout << "Researcher Level: "
        << researcher.GetLevel() << std::endl;

    std::cout << "Total XP: "
        << researcher.GetTotalXP() << std::endl;

    std::cout << "Available XP: "
        << researcher.GetAvailableXP() << std::endl;

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

        std::cout << "Level "
            << learningModules[i].GetModuleLevel()
            << " - "
            << learningModules[i].GetTitle()
            << std::endl;

        std::cout << "   Difficulty: "
            << learningModules[i].GetDifficulty()
            << std::endl;

        std::cout << "   XP Reward: "
            << learningModules[i].GetXPReward()
            << " XP\n";

        std::cout << "   Unlock Cost: "
            << learningModules[i].GetUnlockCost()
            << " XP\n";

        std::cout << "   Required Level: "
            << learningModules[i].GetRequiredLevel()
            << std::endl;

        std::cout << std::endl;
    }

    std::cout << "0. Return to Main Menu\n";
    std::cout << "====================================\n";
}

// ====================================
// Open Learning Path
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

            std::cout << "Module: "
                << selectedModule->GetTitle()
                << std::endl;

            std::cout << "Required Level: "
                << selectedModule->GetRequiredLevel()
                << std::endl;

            std::cout << "Unlock Cost: "
                << selectedModule->GetUnlockCost()
                << " XP\n";

            std::cout << "Available XP: "
                << researcher.GetAvailableXP()
                << std::endl;

            // Check whether the previous module
            // has been completed.
            if (moduleIndex > 0)
            {
                LearningModule* previousModule =
                    &learningModules[moduleIndex - 1];

                if (!previousModule->IsCompleted())
                {
                    std::cout << "\n====================================\n";
                    std::cout << "      PREREQUISITE NOT MET\n";
                    std::cout << "====================================\n";

                    std::cout << "You must complete:\n";

                    std::cout << "Level "
                        << previousModule->GetModuleLevel()
                        << " - "
                        << previousModule->GetTitle()
                        << std::endl;

                    Pause();
                    continue;
                }
            }

            // Check researcher level.
            if (researcher.GetLevel() <
                selectedModule->GetRequiredLevel())
            {
                std::cout << "\nYour researcher level is too low.\n";

                std::cout << "Required Level: "
                    << selectedModule->GetRequiredLevel()
                    << std::endl;

                Pause();
                continue;
            }

            // Check available XP.
            if (researcher.GetAvailableXP() <
                selectedModule->GetUnlockCost())
            {
                std::cout << "\nNot enough available XP.\n";

                Pause();
                continue;
            }

            // Allow the researcher to purchase the module.
            std::cout << "\nPrerequisites completed.\n\n";
            std::cout << "1. Purchase Module\n";
            std::cout << "2. Cancel\n";
            std::cout << "Choice: ";

            int purchaseChoice = GetValidatedChoice(1, 2);

            if (purchaseChoice == 2)
            {
                continue;
            }

            if (researcher.SpendXP(
                selectedModule->GetUnlockCost()))
            {
                selectedModule->UnlockModule();
                // ====================================
// Check for Previously Completed Lab
// ====================================

// Computer Fundamentals requires the
// Terminal Investigation hands-on lab.
//
// If the lab was completed before the
// module was unlocked, complete the
// module now.
                if (moduleIndex == 1 &&
                    labs[0].IsCompleted() &&
                    !selectedModule->IsCompleted())
                {
                    selectedModule->CompleteModule();

                    if (selectedModule->IsCompleted())
                    {
                        researcher.AddXP(
                            selectedModule->GetXPReward());

                        std::cout << "\n====================================\n";
                        std::cout << "       LEARNING MODULE COMPLETE!\n";
                        std::cout << "====================================\n";

                        std::cout
                            << selectedModule->GetTitle()
                            << " completed successfully!\n";

                        std::cout << "\nModule XP Bonus: "
                            << selectedModule->GetXPReward()
                            << " XP\n";

                        std::cout
                            << "\nYour previously completed "
                            << "Terminal Investigation lab "
                            << "satisfied the module requirement.\n";

                        std::cout << "====================================\n";
                    }
                }

                std::cout << "\n====================================\n";
                std::cout << "          MODULE UNLOCKED!\n";
                std::cout << "====================================\n";

                std::cout << selectedModule->GetTitle()
                    << " is now available.\n";

                std::cout << "Available XP: "
                    << researcher.GetAvailableXP()
                    << std::endl;

                Pause();
            }

            continue;
        }

        // ====================================
        // Already Completed Module
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
        // Module Training
        // ====================================

        selectedModule->DisplayModule();

        std::cout << "\n====================================\n";
        std::cout << "           MODULE TRAINING\n";
        std::cout << "====================================\n";

        // Level 0 requires two challenges.
        if (moduleIndex == 0)
        {
            std::cout
                << "Complete both challenges from Start Training:\n\n";

            std::cout << "1. Authorization Basics: ";

            if (challenges[0].IsCompleted())
            {
                std::cout << "Completed\n";
            }
            else
            {
                std::cout << "Not Completed\n";
            }

            std::cout << "2. Scope Basics: ";

            if (challenges[1].IsCompleted())
            {
                std::cout << "Completed\n";
            }
            else
            {
                std::cout << "Not Completed\n";
            }

            std::cout
                << "\nCompleting both challenges will automatically "
                << "complete this learning module.\n";

            std::cout
                << "You will also earn the module XP bonus.\n";
        }
        else if (moduleIndex == 1)
        {
            std::cout
                << "Required Hands-On Lab:\n\n";

            std::cout << "1. Terminal Investigation: ";

            if (labs[0].IsCompleted())
            {
                std::cout << "Completed\n";
            }
            else
            {
                std::cout << "Not Completed\n";
            }

            std::cout
                << "\nComplete Terminal Investigation from "
                << "Hands-On Labs to automatically complete "
                << "Computer Fundamentals.\n";

            std::cout
                << "You will also earn the module XP bonus.\n";
        }
        else
        {
            std::cout
                << "Required training activities for this module "
                << "are still being developed.\n";
        }
        Pause();
    }
    }
// ====================================
// Display Hands-On Labs
// ====================================

void TrainerApp::DisplayLabs() const
{
    std::cout << "\n====================================\n";
    std::cout << "           HANDS-ON LABS\n";
    std::cout << "====================================\n";

    for (int i = 0;
        i < static_cast<int>(labs.size());
        i++)
    {
        std::cout << i + 1 << ". ";

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

        std::cout << labs[i].GetTitle() << std::endl;

        std::cout << "   Difficulty: "
            << labs[i].GetDifficulty()
            << std::endl;

        std::cout << "   Reward: "
            << labs[i].GetXPReward()
            << " XP\n\n";
    }

    std::cout << "0. Return to Main Menu\n";
    std::cout << "====================================\n";
}

// ====================================
// Open Hands-On Labs
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
            static_cast<int>(labs.size()));

        if (choice == 0)
        {
            viewingLabs = false;
            continue;
        }

        Lab* selectedLab = &labs[choice - 1];

        // Prevent access to locked labs.
        if (!selectedLab->IsUnlocked())
        {
            std::cout << "\n====================================\n";
            std::cout << "             LAB LOCKED\n";
            std::cout << "====================================\n";

            std::cout << selectedLab->GetTitle()
                << " is not available yet.\n";

            std::cout << "Complete earlier training first.\n";

            Pause();
            continue;
        }

        // Prevent duplicate XP rewards.
        if (selectedLab->IsCompleted())
        {
            selectedLab->DisplayLab();
            selectedLab->DisplayObjectives();

            std::cout << "\nYou already completed this lab.\n";
            std::cout << "No additional XP will be awarded.\n";

            Pause();
            continue;
        }

        // Launch the first simulated lab.
        if (choice == 1)
        {
            RunTerminalInvestigationLab(*selectedLab);
        }
    }
}

// ====================================
// Terminal Investigation Lab
// ====================================

void TrainerApp::RunTerminalInvestigationLab(Lab& lab)
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

        std::getline(std::cin, command);

        // ====================================
        // Help Command
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
        // Identify Current User
        // ====================================

        else if (command == "whoami")
        {
            std::cout << "bbt-training\\researcher\n";

            if (!lab.IsObjectiveCompleted(1))
            {
                lab.CompleteObjective(1);

                std::cout
                    << "[OBJECTIVE COMPLETE] "
                    << "Current user identified.\n";
            }
        }

        // ====================================
        // List Training Directory
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
        // Read Training File
        // ====================================

        else if (command == "type training.txt")
        {
            // Require the directory objective first.
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

        // ====================================
        // Optional Notes File
        // ====================================

        else if (command == "type notes.txt")
        {
            std::cout << "Hint: Inspect training.txt.\n";
        }

        // ====================================
        // Display Lab Progress
        // ====================================

        else if (command == "status")
        {
            lab.DisplayObjectives();
        }

        // ====================================
        // Exit Lab
        // ====================================

        else if (command == "exit")
        {
            labRunning = false;
        }

        else if (command.empty())
        {
            continue;
        }

        // ====================================
        // Invalid Lab Command
        // ====================================

        else
        {
            std::cout << "'"
                << command
                << "' is not a recognized lab command.\n";

            std::cout
                << "Type help to view available commands.\n";
        }

        // ====================================
        // Automatic Lab Completion
        // ====================================

        if (lab.AreAllObjectivesCompleted() &&
            !lab.IsCompleted())
        {
            bool completed = lab.CompleteLab();

            if (completed)
            {
                // Award the lab's XP once.
                researcher.AddXP(lab.GetXPReward());
                
        // ====================================
        // Connect Lab to Learning Module
        // ====================================

                     // Terminal Investigation is the required
                     // hands-on lab for Computer Fundamentals.
                if (lab.GetTitle() == "Terminal Investigation" &&
                    learningModules[1].IsUnlocked() &&
                    !learningModules[1].IsCompleted())
                {
                    learningModules[1].CompleteModule();

                    // Award the module XP bonus once.
                    if (learningModules[1].IsCompleted())
                    {
                        researcher.AddXP(
                            learningModules[1].GetXPReward());

                        std::cout << "\n====================================\n";
                        std::cout << "       LEARNING MODULE COMPLETE!\n";
                        std::cout << "====================================\n";

                        std::cout
                            << learningModules[1].GetTitle()
                            << " completed successfully!\n";

                        std::cout << "\nModule XP Bonus: "
                            << learningModules[1].GetXPReward()
                            << " XP\n";

                        std::cout
                            << "\nTerminal Investigation satisfied "
                            << "the required hands-on training.\n";

                        std::cout << "====================================\n";
                    }
                }

                std::cout << "\n====================================\n";
                std::cout << "            LAB COMPLETE!\n";
                std::cout << "====================================\n";

                std::cout << lab.GetTitle()
                    << " completed successfully.\n";

                std::cout
                    << "\nAll required objectives were validated.\n";

                std::cout << "\nXP Earned: "
                    << lab.GetXPReward()
                    << std::endl;

                std::cout << "Total XP: "
                    << researcher.GetTotalXP()
                    << std::endl;

                std::cout << "Available XP: "
                    << researcher.GetAvailableXP()
                    << std::endl;

                std::cout << "====================================\n";

                labRunning = false;
            }
        }
    }

    if (!lab.IsCompleted())
    {
        std::cout << "\nLab exited before completion.\n";

        std::cout
            << "Your completed objectives remain "
            << "available during this session.\n";
    }

    Pause();
}

// ====================================
// Display Training Challenges
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
        std::cout << i + 1 << ". "
            << challenges[i].GetTitle()
            << std::endl;

        std::cout << "   Category: "
            << challenges[i].GetCategory()
            << std::endl;

        std::cout << "   Difficulty: "
            << challenges[i].GetDifficulty()
            << std::endl;

        std::cout << "   Reward: "
            << challenges[i].GetXPReward()
            << " XP\n";

        if (challenges[i].IsCompleted())
        {
            std::cout << "   Status: Completed\n";
        }
        else
        {
            std::cout << "   Status: Not Completed\n";
        }

        std::cout << std::endl;
    }

    std::cout << "====================================\n";
}

// ====================================
// Start Training
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
        std::cout << i + 1 << ". "
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

    // Do not award XP for previously completed challenges.
    if (selectedChallenge->IsCompleted())
    {
        std::cout
            << "\nYou already completed this challenge.\n";

        return;
    }

    selectedChallenge->DisplayQuestion();

    std::cout << "\nEnter your answer: ";

    int answer = GetValidatedChoice(
        1,
        selectedChallenge->GetOptionCount());

    if (selectedChallenge->IsCorrectAnswer(answer))
    {
        // Save the level before awarding XP.
        int oldLevel = researcher.GetLevel();

        // Mark the challenge as completed.
        selectedChallenge->CompleteChallenge();

        // Award challenge XP.
        researcher.AddXP(
            selectedChallenge->GetXPReward());

        std::cout << "\n====================================\n";
        std::cout << "        CHALLENGE COMPLETED!\n";
        std::cout << "====================================\n";

        std::cout << "Correct!\n";

        std::cout << "You earned "
            << selectedChallenge->GetXPReward()
            << " XP.\n";

        // ====================================
        // Automatic Learning Module Completion
        // ====================================

        // Level 0 requires:
        // 1. Authorization Basics
        // 2. Scope Basics
        //
        // Both must be completed before
        // the learning module can be finished.
        //
        // The module bonus is awarded only once.

        if (challenges[0].IsCompleted() &&
            challenges[1].IsCompleted() &&
            !learningModules[0].IsCompleted())
        {
            // Complete Learning Module 0.
            learningModules[0].CompleteModule();

            // Verify the module was completed.
            if (learningModules[0].IsCompleted())
            {
                // Award the module XP bonus.
                researcher.AddXP(
                    learningModules[0].GetXPReward());

                std::cout << "\n====================================\n";
                std::cout << "       LEARNING MODULE COMPLETE!\n";
                std::cout << "====================================\n";

                std::cout
                    << learningModules[0].GetTitle()
                    << " completed successfully!\n";

                std::cout << "\nModule XP Bonus: "
                    << learningModules[0].GetXPReward()
                    << " XP\n";

                std::cout
                    << "\nYou can now unlock "
                    << "Computer Fundamentals.\n";

                std::cout << "====================================\n";
            }
        }

        // ====================================
        // Display Updated Researcher Progress
        // ====================================

        std::cout << "\nTotal XP: "
            << researcher.GetTotalXP()
            << std::endl;

        std::cout << "Available XP: "
            << researcher.GetAvailableXP()
            << std::endl;

        // Check whether the researcher gained a level.
        if (researcher.GetLevel() > oldLevel)
        {
            std::cout << "\nLEVEL UP!\n";

            std::cout << "You are now Level "
                << researcher.GetLevel()
                << "!\n";
        }
    }
    else
    {
        std::cout << "\n====================================\n";
        std::cout << "          TRY AGAIN\n";
        std::cout << "====================================\n";

        std::cout << "That answer was not correct.\n";
        std::cout << "No XP was lost.\n";
    }
}

// ====================================
// Main Menu Choice Handling
// ====================================

void TrainerApp::HandleChoice(int choice)
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
    std::cout << "\nPress Enter to continue...";
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

        int choice = GetValidatedChoice(1, 6);

        HandleChoice(choice);

        // Learning Path and Hands-On Labs
        // handle their own pause messages.
        if (running &&
            choice != 2 &&
            choice != 3)
        {
            Pause();
        }
    }
}