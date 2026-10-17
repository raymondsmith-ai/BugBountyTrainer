#pragma once

#include <sqlite3.h>
#include <string>

// ====================================
// BugBountyTrainer SQL Database
// ====================================

class Database
{
private:
    sqlite3* database = nullptr;

public:
    Database();
    ~Database();

    // Prevent accidental copying.
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    // Open the training database.
    bool Initialize();

    // Create the fictional training tables.
    bool CreateTables();

    // Insert sample training records.
    bool SeedData();

    // Close the database connection.
    void Close();

    // Check database availability.
    bool IsConnected() const;
};