#include <iostream>
#include <string>
#include "Researcher.h"

int main()
{
    std::string researcherName;

    std::cout << "================================\n";
    std::cout << "     BUG BOUNTY TRAINER\n";
    std::cout << "================================\n\n";

    std::cout << "Enter your researcher name: ";
    std::getline(std::cin, researcherName);

    Researcher player(researcherName);

    player.DisplayProfile();

    std::cout << "\nPress Enter to exit...";
    std::cin.get();

    return 0;
}