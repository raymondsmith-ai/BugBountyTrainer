#include <iostream>
#include <string>

#include "../include/Researcher.h"
#include "../include/Challenge.h"

int main()
{
    std::string researcherName;

    std::cout << "====================================\n";
    std::cout << "        BUG BOUNTY TRAINER\n";
    std::cout << "====================================\n\n";

    // Ask the user to create their researcher profile.
    std::cout << "Enter your researcher name: ";
    std::getline(std::cin, researcherName);

    Researcher researcher(researcherName);

    // Create the first training challenge.
    Challenge authorizationChallenge(
        "Authorization Basics",
        "Identify whether a target is authorized for security testing.",
        100
    );

    bool running = true;

    while (running)
    {
        int choice = 0;

        std::cout << "\n====================================\n";
        std::cout << "              MAIN MENU\n";
        std::cout << "====================================\n";
        std::cout << "1. View Researcher Profile\n";
        std::cout << "2. View Challenge\n";
        std::cout << "3. Complete Challenge\n";
        std::cout << "4. Exit\n";
        std::cout << "====================================\n";
        std::cout << "Enter choice: ";

        std::cin >> choice;

        switch (choice)
        {
        case 1:
            researcher.DisplayProfile();
            break;

        case 2:
            authorizationChallenge.DisplayChallenge();
            break;

        case 3:
            if (!authorizationChallenge.IsCompleted())
            {
                authorizationChallenge.CompleteChallenge();

                researcher.AddXP(
                    authorizationChallenge.GetXPReward()
                );

                std::cout << "\nChallenge completed!\n";
                std::cout << "You earned "
                    << authorizationChallenge.GetXPReward()
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

    return 0;
}