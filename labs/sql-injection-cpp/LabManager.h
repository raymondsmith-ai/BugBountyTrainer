#pragma once

#include <sqlite3.h>
#include <string>

class LabManager
{
public:
    // Execute a predefined SQL exercise.
    static std::string RunExercise(
        sqlite3* database,
        int exerciseId);
};