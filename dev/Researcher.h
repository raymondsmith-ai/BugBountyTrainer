#pragma once

#include <string>

class Researcher
{
private:
    std::string name;
    int level;
    int xp;

public:
    // Constructor
    Researcher(std::string researcherName);

    // Displays the researcher's information
    void DisplayProfile() const;

    // Adds XP to the researcher
    void AddXP(int amount);
};