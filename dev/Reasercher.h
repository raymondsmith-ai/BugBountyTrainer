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
    Researcher(const std::string& researcherName);

    // Getters
    std::string GetName() const;
    int GetLevel() const;
    int GetXP() const;

    // Displays the researcher's information
    void DisplayProfile() const;

    // Adds XP to the researcher
    void AddXP(int amount);
};