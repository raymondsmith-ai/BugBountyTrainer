#pragma once

#include <cstddef>
#include <vector>

#include "SQLLesson.h"

// ====================================
// SQL Academy
// Manages 13 SQL training modules
// ====================================

class SQLAcademy
{
private:
    std::vector<SQLLesson> lessons;

    // Initialize the training curriculum.
    void InitializeLessons();
    void LoadCurriculum();

    // Display available training modules.
    void DisplayMenu() const;

    // Display lesson content and examples.
    void OpenLesson(std::size_t lessonIndex);

    // Run a lesson assessment.
    void RunAssessment(std::size_t lessonIndex);

    // Display guided SQL exercises.
    void RunGuidedPractice(std::size_t lessonIndex) const;

    // Validate menu selections.
    int GetValidatedChoice(int min, int max) const;

    // Check whether a lesson is unlocked.
    bool IsLessonUnlocked(std::size_t lessonIndex) const;

public:
    SQLAcademy();

    // Launch the SQL Academy.
    void Run();

    // Check lesson completion.
    bool IsLessonComplete(int lessonId) const;

    // Restore saved lesson completion.
    void RestoreLessonCompletion(int lessonId, bool completed);

    // Retrieve lesson information.
    const std::vector<SQLLesson>& GetLessons() const;
};