#include "../include/TrainerApp.h"
#include <iostream>

// Constructor
TrainerApp::TrainerApp(const std::string& researcherName)
    : researcher(researcherName),
    challenge(
        "Authorization Basics",
        "Identify whether a target is authorized for security testing.",
        100),
    running(true)
{
}

// Displays the main menu
void TrainerApp::DisplayMenu() const
{
    std::cout << "\n====================================\n";
    std::cout << "              MAIN MENU\n";
    std::cout << "====================================\n";
    std::cout << "1. View Researcher Profile\n";
    std::cout << "2. View Challenge\n";
    std::cout << "3. Complete Challenge\n";
    std::cout << "4. Exit\n";
    std::cout << "====================================\n";
    std::cout << "Enter choice: ";
}

// Handles the user's menu selection
void TrainerApp::HandleChoice(int choice)
{
    switch (choice)
    {
    case 1:
        researcher.DisplayProfile();
        break;

    case 2:
        challenge.DisplayChallenge();
        break;

    case 3:
        if (!challenge.IsCompleted())
        {
            challenge.CompleteChallenge();
            researcher.AddXP(challenge.GetXPReward());

            std::cout << "\nChallenge completed!\n";
            std::cout << "You earned "
                << challenge.GetXPReward()
                << " XP!\n";
        }
        else
        {
            std::cout << "\nYou already completed this challenge.\n";
        }
        break;

    case 4:
        running = false;
        std::cout << "\nExiting Bug Bounty Trainer...\n";
        break;

    default:
        std::cout << "\nInvalid choice. Please try again.\n";
        break;
    }
}

// Runs the main program loop
void TrainerApp::Run()
{
    while (running)
    {
        int choice = 0;

        DisplayMenu();
        std::cin >> choice;

        HandleChoice(choice);
    }
}