#include <iostream>
#include <string>
#include <sstream>

#include "Researcher.h"

// Displays the application title.
void DisplayTitle()
{
    std::cout << "====================================\n";
    std::cout << "        BUG BOUNTY TRAINER\n";
    std::cout << "====================================\n";
    std::cout << "Practice. Learn. Level Up.\n";
    std::cout << "====================================\n";
}

// Displays the main menu.
void DisplayMainMenu()
{
    std::cout << "\n========== MAIN MENU ==========\n";
    std::cout << "1. Start Training\n";
    std::cout << "2. View Researcher Profile\n";
    std::cout << "3. Exit\n";
    std::cout << "===============================\n";
}

// Gets a valid menu choice from the user.
int GetMenuChoice()
{
    std::string input;
    int choice = 0;
    bool validChoice = false;

    while (validChoice == false)
    {
        std::cout << "Enter your choice (1-3): ";
        std::getline(std::cin, input);

        // Convert the user's string input into an integer.
        std::stringstream converter(input);

        char extraCharacter;

        // Check that the input contains an integer
        // and does not contain extra characters.
        if ((converter >> choice) && !(converter >> extraCharacter))
        {
            // Check that the number is inside the menu range.
            if (choice >= 1 && choice <= 3)
            {
                validChoice = true;
            }
            else
            {
                std::cout << "\nInvalid choice.\n";
                std::cout << "Please enter a number from 1 to 3.\n\n";
            }
        }
        else
        {
            std::cout << "\nInvalid input.\n";
            std::cout << "Please enter a number from 1 to 3.\n\n";
        }
    }

    return choice;
}

// Pauses the program until the user presses Enter.
void PauseProgram()
{
    std::cout << "\nPress Enter to return to the main menu...";
    std::string pause;
    std::getline(std::cin, pause);
}

int main()
{
    DisplayTitle();

    // Get the researcher's name.
    std::string researcherName;

    while (researcherName.empty())
    {
        std::cout << "\nEnter your researcher name: ";
        std::getline(std::cin, researcherName);

        if (researcherName.empty())
        {
            std::cout << "Researcher name cannot be empty.\n";
        }
    }

    // Create the researcher.
    Researcher researcher(researcherName);

    std::cout << "\nWelcome, " << researcher.GetName() << "!\n";

    bool running = true;

    // Main application loop.
    while (running)
    {
        DisplayMainMenu();

        int choice = GetMenuChoice();

        switch (choice)
        {
        case 1:
            std::cout << "\n========== TRAINING ==========\n";
            std::cout << "Training challenges are coming in Week 2!\n";
            std::cout << "==============================\n";

            PauseProgram();
            break;

        case 2:
            researcher.DisplayProfile();

            PauseProgram();
            break;

        case 3:
            std::cout << "\nThanks for using Bug Bounty Trainer!\n";
            std::cout << "Keep learning and keep hunting.\n";

            running = false;
            break;
        }
    }

    return 0;
}