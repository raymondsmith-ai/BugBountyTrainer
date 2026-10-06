#pragma once

#include "Researcher.h"
#include "Challenge.h"

class TrainerApp
{
private:
    Researcher researcher;
    Challenge challenge;
    bool running;

    void DisplayMenu() const;
    void HandleChoice(int choice);

public:
    TrainerApp(const std::string& researcherName);

    void Run();
};