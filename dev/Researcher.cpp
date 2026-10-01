#include "Researcher.h"
#include <iostream>

// Constructor
Researcher::Researcher(std::string researcherName)
{
    name = researcherName;
    level = 1;
    xp = 0;
}

// Displays the researcher's profile information
void Researcher::DisplayProfile() const
{
    std::cout << "\n--- Researcher Profile ---\n";
    std::cout << "Name: " << name << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "XP: " << xp << std::endl;
}

// Adds XP to the researcher
void Researcher::AddXP(int amount)
{
    xp += amount;
}