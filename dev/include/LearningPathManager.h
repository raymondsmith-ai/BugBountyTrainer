#pragma once

#include <functional>
#include <string>
#include <vector>

#include "Researcher.h"
#include "LearningModule.h"
#include "Challenge.h"
#include "Lab.h"

// Owns learning-path screens, module prerequisites, unlocking, and assessments.
// It operates on TrainerApp's existing objects; it does not copy saved progress.
class LearningPathManager
{
public:
    using ChoiceReader = std::function<int(int, int)>;
    using PauseAction = std::function<void()>;
    using AnswerShuffler = std::function<std::vector<int>(const std::string&, int, int)>;
    using LetterAnswerReader = std::function<int(int)>;

    static void Display(
        const Researcher& researcher,
        const std::vector<LearningModule>& learningModules);

    static void Run(
        Researcher& researcher,
        std::vector<LearningModule>& learningModules,
        const std::vector<Challenge>& challenges,
        const std::vector<Lab>& labs,
        const ChoiceReader& getValidatedChoice,
        const PauseAction& pause,
        const AnswerShuffler& shuffleAnswerPositions,
        const LetterAnswerReader& readLetterAnswer);
};
