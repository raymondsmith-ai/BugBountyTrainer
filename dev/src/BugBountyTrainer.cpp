#include <iostream>
#include <string>

#include "../include/TrainerApp.h"

int main()
{
    std::string researcherName;

    std::cout << "====================================\n";
    std::cout << "        BUG BOUNTY TRAINER\n";
    std::cout << "====================================\n\n";

    std::cout << "Enter your researcher name: ";
    std::getline(std::cin, researcherName);

    TrainerApp app(researcherName);

    app.Run();

    return 0;
}