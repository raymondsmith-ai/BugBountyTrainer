#pragma once

#include <string>
#include <vector>

#include "Researcher.h"
#include "Challenge.h"

// ====================================
// SaveManager Class
// ====================================
// Handles saving and loading progress.
// ====================================

class SaveManager
{
public:

    // Save researcher information
    // and completed challenges.
    static bool SaveProgress(
        const Researcher& researcher,
        const std::vector<Challenge>& challenges,
        const std::string& filename);

    // Load researcher information
    // and completed challenges.
    static bool LoadProgress(
        Researcher& researcher,
        std::vector<Challenge>& challenges,
        const std::string& filename);
};