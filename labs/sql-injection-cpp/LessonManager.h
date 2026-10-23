#pragma once

#include <string>

class LessonManager
{
public:
    // Retrieve a lesson by its module ID.
    static std::string GetLesson(int moduleId);
};