#include "../include/TrainerApp.h"

#include <iostream>
#include <limits>

// Constructor
TrainerApp::TrainerApp(const std::string& researcherName)
    : researcher(researcherName),
    running(true)
{
    // Challenge 1
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

    // Challenge 2
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

    // Challenge 3
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
}

// Displays the main menu.
void TrainerApp::DisplayMenu() const
{
    std::cout << "\n====================================\n";
    std::cout << "        BUG BOUNTY TRAINER\n";
    std::cout << "====================================\n";
    std::cout << "1. View Researcher Profile\n";
    std::cout << "2. Start Training\n";
    std::cout << "3. View Challenges\n";
    std::cout << "4. Exit\n";
    std::cout << "====================================\n";
    std::cout << "Enter a number from 1 to 4: ";
}

// Gets a valid integer from the user.
int TrainerApp::GetValidatedChoice(
    int minimum,
    int maximum) const
{
    int choice;

    while (true)
    {
        std::cin >> choice;

        // Handles letters or invalid input.
        if (std::cin.fail())
        {
            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');

            std::cout << "\nInvalid input.\n";
            std::cout << "Please enter a number from "
                << minimum
                << " to "
                << maximum
                << ": ";

            continue;
        }

        // Clear anything remaining on the line.
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');

        // Check the valid number range.
        if (choice < minimum || choice > maximum)
        {
            std::cout << "\nInvalid selection.\n";
            std::cout << "Please enter a number from "
                << minimum
                << " to "
                << maximum
                << ": ";

            continue;
        }

        return choice;
    }
}

// Displays all available challenges.
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
            << " XP"
            << std::endl;

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

// Starts the training system.
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

    // Prevent duplicate XP.
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

    // Correct answer.
    if (selectedChallenge->IsCorrectAnswer(answer))
    {
        int oldLevel = researcher.GetLevel();

        selectedChallenge->CompleteChallenge();

        researcher.AddXP(
            selectedChallenge->GetXPReward());

        std::cout << "\n====================================\n";
        std::cout << "        CHALLENGE COMPLETED!\n";
        std::cout << "====================================\n";

        std::cout << "Correct!\n";

        std::cout << "You earned "
            << selectedChallenge->GetXPReward()
            << " XP.\n";

        std::cout << "Current XP: "
            << researcher.GetXP()
            << std::endl;

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
        std::cout << "You can try this challenge again.\n";
    }
}

// Handles main menu choices.
void TrainerApp::HandleChoice(int choice)
{
    switch (choice)
    {
    case 1:
        researcher.DisplayProfile();
        break;

    case 2:
        StartTraining();
        break;

    case 3:
        DisplayChallenges();
        break;

    case 4:
        running = false;

        std::cout
            << "\nThank you for using Bug Bounty Trainer!\n";

        std::cout
            << "Keep learning and test responsibly.\n";

        break;
    }
}

// Pauses the application.
void TrainerApp::Pause() const
{
    std::cout
        << "\nPress Enter to return to the main menu...";

    std::cin.get();
}

// Runs the main program loop.
void TrainerApp::Run()
{
    while (running)
    {
        DisplayMenu();

        int choice = GetValidatedChoice(1, 4);

        HandleChoice(choice);

        if (running)
        {
            Pause();
        }
    }
}