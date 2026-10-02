#in#include "Researcher.h"

#include <iostream>

// Constructor
// Every new researcher starts at Level 1 with 0 XP.
Researcher::Researcher(const std::string& researcherName)
{
    name = researcherName;
    level = 1;
    xp = 0;
}

// Returns the researcher's name.
std::string Researcher::GetName() const
{
    return name;
}

// Returns the researcher's current level.
int Researcher::GetLevel() const
{
    return level;
}

// Returns the researcher's current XP.
int Researcher::GetXP() const
{
    return xp;
}

// Displays the researcher's profile.
void Researcher::DisplayProfile() const
{
    std::cout << "\n====================================\n";
    std::cout << "        RESEARCHER PROFILE\n";
    std::cout << "====================================\n";

    std::cout << "Name:  " << name << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "XP:    " << xp << std::endl;

    std::cout << "====================================\n";
}

// Adds XP to the researcher.
// Level progression will be added during Week 2.
void Researcher::AddXP(int amount)
{
    if (amount > 0)
    {
        xp += amount;
    }
}