#include "Database.h"

#include <iostream>

// ====================================
// Constructor
// ====================================

Database::Database()
{
}

// ====================================
// Destructor
// ====================================

Database::~Database()
{
    Close();
}

// ====================================
// Initialize Database
// ====================================

bool Database::Initialize()
{
    if (database != nullptr)
    {
        return true;
    }

    // In-memory SQLite database.
    // Recreated when the server restarts.
    const int result = sqlite3_open(
        ":memory:",
        &database);

    if (result != SQLITE_OK)
    {
        std::cerr << "Failed to initialize SQLite.\n";
        Close();
        return false;
    }

    if (!CreateTables())
    {
        Close();
        return false;
    }

    if (!SeedData())
    {
        Close();
        return false;
    }

    return true;
}

// ====================================
// Create Training Tables
// ====================================

bool Database::CreateTables()
{
    const char* sql = R"(
        CREATE TABLE IF NOT EXISTS products (
            id INTEGER PRIMARY KEY,
            name TEXT NOT NULL,
            category TEXT NOT NULL,
            price INTEGER NOT NULL,
            published INTEGER NOT NULL
        );

        CREATE TABLE IF NOT EXISTS training_users (
            id INTEGER PRIMARY KEY,
            username TEXT NOT NULL,
            role TEXT NOT NULL
        );

        CREATE TABLE IF NOT EXISTS training_flags (
            id INTEGER PRIMARY KEY,
            challenge TEXT NOT NULL,
            flag TEXT NOT NULL
        );
    )";

    char* errorMessage = nullptr;

    const int result = sqlite3_exec(
        database,
        sql,
        nullptr,
        nullptr,
        &errorMessage);

    if (result != SQLITE_OK)
    {
        std::cerr << "SQLite table creation failed: "
                  << (errorMessage ? errorMessage : "Unknown error")
                  << '\n';

        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

// ====================================
// Insert Fictional Training Data
// ====================================

bool Database::SeedData()
{
    const char* sql = R"(
        INSERT INTO products VALUES
            (1, 'Training Notebook', 'Books', 12, 1),
            (2, 'Practice Keyboard', 'Hardware', 35, 1),
            (3, 'Network Cable', 'Hardware', 15, 1),
            (4, 'Hidden Training Record', 'Internal', 0, 0);

        INSERT INTO training_users VALUES
            (1, 'student', 'researcher'),
            (2, 'instructor', 'trainer'),
            (3, 'lab_admin', 'administrator');

        INSERT INTO training_flags VALUES
            (1, 'Basic SQL Injection', 'BBT-TRAINING-001'),
            (2, 'Boolean Query Manipulation', 'BBT-TRAINING-002'),
            (3, 'Database Investigation', 'BBT-TRAINING-003');
    )";

    char* errorMessage = nullptr;

    const int result = sqlite3_exec(
        database,
        sql,
        nullptr,
        nullptr,
        &errorMessage);

    if (result != SQLITE_OK)
    {
        std::cerr << "SQLite seed failed: "
                  << (errorMessage ? errorMessage : "Unknown error")
                  << '\n';

        sqlite3_free(errorMessage);
        return false;
    }

    return true;
}

// ====================================
// Close Database
// ====================================

void Database::Close()
{
    if (database != nullptr)
    {
        sqlite3_close(database);
        database = nullptr;
    }
}

// ====================================
// Check Connection
// ====================================

bool Database::IsConnected() const
{
    return database != nullptr;
}
// ====================================
// Get SQLite Connection
// ====================================

sqlite3* Database::GetConnection() const
{
    return database;
}