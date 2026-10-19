#pragma once

#include <string>
#include <vector>

// ====================================
// SQL Academy Assessment Question
// ====================================

struct SQLQuestion
{
    std::string question;
    std::vector<std::string> options;

    // Answer numbering starts at 1.
    int correctAnswer = 1;

    std::string explanation;
};

// ====================================
// SQL Academy Lesson Section
// ====================================

struct SQLLessonSection
{
    std::string title;
    std::string content;
};

// ====================================
// SQL Academy Guided Exercise
// ====================================

struct SQLExercise
{
    std::string instruction;
    std::string exampleQuery;
};

// ====================================
// SQL Academy Lesson
// ====================================

struct SQLLesson
{
    int id = 0;

    std::string title;
    std::string difficulty;
    std::string description;

    // Educational lesson content.
    std::vector<SQLLessonSection> sections;

    // Guided SQL practice.
    std::vector<SQLExercise> exercises;

    // Assessment questions.
    std::vector<SQLQuestion> questions;

    // XP awarded for first-time completion.
    int xpReward = 0;

    // Tracks lesson completion.
    bool completed = false;
};