#pragma once

#include <string>

class Researcher
{
private:
    std::string name;

    int level;

    // Lifetime XP. This never decreases.
    int totalXP;

    // XP that can be spent on modules and tools.
    int availableXP;

public:
    // Constructor.
    Researcher(const std::string& researcherName);

    // Getters.
    std::string GetName() const;
    int GetLevel() const;

    // GetXP is kept so existing code continues working.
    int GetXP() const;

    int GetTotalXP() const;
    int GetAvailableXP() const;

    // Researcher functions.
    void DisplayProfile() const;

    // Adds XP to both lifetime and spendable XP.
    void AddXP(int amount);

    // Attempts to spend available XP.
    // Returns true if the purchase succeeds.
    bool SpendXP(int amount);
};