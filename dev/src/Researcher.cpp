#include "../include/Researcher.h"

#include <iostream>

// Constructor.
// Every new researcher starts at Level 1 with 0 XP.
Researcher::Researcher(const std::string& researcherName)
{
    name = researcherName;

    level = 1;

    totalXP = 0;
    availableXP = 0;
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

// Kept for compatibility with existing code.
// Returns lifetime XP.
int Researcher::GetXP() const
{
    return totalXP;
}

// Returns lifetime XP.
int Researcher::GetTotalXP() const
{
    return totalXP;
}

// Returns XP currently available to spend.
int Researcher::GetAvailableXP() const
{
    return availableXP;
}

// Displays the researcher's profile.
void Researcher::DisplayProfile() const
{
    std::cout << "\n====================================\n";
    std::cout << "        RESEARCHER PROFILE\n";
    std::cout << "====================================\n";

    std::cout << "Name:         "
        << name
        << std::endl;

    std::cout << "Level:        "
        << level
        << std::endl;

    std::cout << "Total XP:     "
        << totalXP
        << std::endl;

    std::cout << "Available XP: "
        << availableXP
        << std::endl;

    std::cout << "====================================\n";
}

// Adds XP to both lifetime XP and spendable XP.
void Researcher::AddXP(int amount)
{
    if (amount <= 0)
    {
        return;
    }

    totalXP += amount;
    availableXP += amount;

    // Gain a new level every 200 lifetime XP.
    while (totalXP >= level * 200)
    {
        level++;
    }
}

// Attempts to spend XP.
// Returns true if the researcher has enough XP.
bool Researcher::SpendXP(int amount)
{
    if (amount < 0)
    {
        return false;
    }

    if (availableXP < amount)
    {
        return false;
    }

    availableXP -= amount;

    return true;
}