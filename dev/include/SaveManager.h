#pragma once

#include <string>
#include <vector>

#include "Researcher.h"
#include "Challenge.h"
#include "LearningModule.h"

// ====================================
// SaveManager Class
// ====================================
// Handles saving and loading researcher,
// challenge, and learning module progress.
// ====================================

class SaveManager
{
public:

    // Save researcher information,
    // completed challenges, and modules.
    static bool SaveProgress(
        const Researcher& researcher,
        const std::vector<Challenge>& challenges,
        const std::vector<LearningModule>& learningModules,
        const std::string& filename);

    // Restore researcher information,
    // completed challenges, and modules.
    static bool LoadProgress(
        Researcher& researcher,
        std::vector<Challenge>& challenges,
        std::vector<LearningModule>& learningModules,
        const std::string& filename);
};