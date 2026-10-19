#include "LabManager.h"

#include <sstream>
#include <string>

std::string LabManager::RunExercise(
    sqlite3* database,
    int exerciseId)
{
    if (database == nullptr)
    {
        return "Error: Database is unavailable.";
    }

    std::string query;

    switch (exerciseId)
    {
    case 1:
        query = "SELECT * FROM products;";
        break;

    case 2:
        query = "SELECT name, price FROM products;";
        break;

    case 3:
        query = "SELECT name FROM products WHERE published = 1;";
        break;

    default:
        return "Error: Unknown exercise.";
    }

    sqlite3_stmt* statement = nullptr;

    const int result = sqlite3_prepare_v2(
        database,
        query.c_str(),
        -1,
        &statement,
        nullptr);

    if (result != SQLITE_OK)
    {
        return "Error: Unable to prepare SQL query.";
    }

    std::ostringstream output;

    output << "Exercise: " << exerciseId << '\n';
    output << "SQL Query: " << query << "\n\n";

    const int columnCount = sqlite3_column_count(statement);

    // Display column names.
    for (int column = 0; column < columnCount; ++column)
    {
        if (column > 0)
        {
            output << " | ";
        }

        output << sqlite3_column_name(statement, column);
    }

    output << '\n';

    int rowCount = 0;
    int stepResult = SQLITE_OK;

    // Retrieve actual SQLite records.
    while ((stepResult = sqlite3_step(statement)) == SQLITE_ROW)
    {
        ++rowCount;

        for (int column = 0; column < columnCount; ++column)
        {
            if (column > 0)
            {
                output << " | ";
            }

            const unsigned char* value =
                sqlite3_column_text(statement, column);

            if (value != nullptr)
            {
                output << reinterpret_cast<const char*>(value);
            }
            else
            {
                output << "NULL";
            }
        }

        output << '\n';
    }

    if (stepResult != SQLITE_DONE)
    {
        sqlite3_finalize(statement);
        return "Error: SQL query execution failed.";
    }

    sqlite3_finalize(statement);

    output << "\nRows returned: " << rowCount << '\n';

    return output.str();
}