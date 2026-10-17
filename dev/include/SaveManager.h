#pragma once

#include <string>
#include <vector>

#include "Researcher.h"
#include "Challenge.h"
#include "LearningModule.h"
#include "SQLFundamentals.h"
#include "SQLInjection.h"

// ====================================
// SaveManager Class
// ====================================
// Handles persistent researcher progress,
// completed challenges, learning modules,
// SQL Fundamentals, and SQL Injection.
//
// Supports BBT_SAVE_V2 through BBT_SAVE_V5.
// ====================================

class SaveManager
{
public:

    // ====================================
    // Save Progress
    // ====================================
    // Saves researcher information,
    // challenge completion,
    // learning module progression,
    // SQL Fundamentals progress,
    // SQL Injection Stage 2 progress,
    // and one-time reward tracking.
    // ====================================

    static bool SaveProgress(
        const Researcher& researcher,
        const std::vector<Challenge>& challenges,
        const std::vector<LearningModule>& learningModules,
        const SQLFundamentals& sqlFundamentals,
        const SQLInjection& sqlInjection,
        const std::string& filename);

    // ====================================
    // Load Progress
    // ====================================
    // Loads existing researcher information,
    // challenge completion,
    // learning module progression,
    // SQL Fundamentals progress,
    // SQL Injection Stage 2 progress,
    // and reward completion flags.
    //
    // Supports older V2, V3, and V4 saves.
    // ====================================

    static bool LoadProgress(
        Researcher& researcher,
        std::vector<Challenge>& challenges,
        std::vector<LearningModule>& learningModules,
        SQLFundamentals& sqlFundamentals,
        SQLInjection& sqlInjection,
        const std::string& filename);
};