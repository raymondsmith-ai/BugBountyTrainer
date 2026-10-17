#include "LessonManager.h"

std::string LessonManager::GetLesson(int moduleId)
{
    if (moduleId == 1)
    {
        return R"({
            "id": 1,
            "title": "Introduction to Databases",
            "difficulty": "Beginner",
            "estimated_minutes": 30,
            "description": "Learn how databases organize and retrieve information.",
            "sections": [
                {
                    "title": "What Is a Database?",
                    "content": "A database is an organized collection of information. Applications use databases to store, search, update, and retrieve information."
                },
                {
                    "title": "Database Tables",
                    "content": "A relational database stores information in tables. Each table contains rows and columns."
                },
                {
                    "title": "Rows and Columns",
                    "content": "A row represents one record. A column represents a specific attribute, such as a product name or price."
                },
                {
                    "title": "Primary Keys",
                    "content": "A primary key uniquely identifies each record in a table."
                },
                {
                    "title": "Introduction to SQLite",
                    "content": "SQLite is a relational database engine. BugBountyTrainer uses SQLite to power its hands-on SQL training laboratories."
                },
                {
                    "title": "Your First SQL Query",
                    "content": "The SELECT statement retrieves information from a database. For example, SELECT * FROM products; retrieves every column from the products table."
                }
            ],
            "guided_practice": [
                {
                    "step": 1,
                    "instruction": "Examine the products table.",
                    "query": "SELECT * FROM products;"
                },
                {
                    "step": 2,
                    "instruction": "Retrieve product names and prices.",
                    "query": "SELECT name, price FROM products;"
                },
                {
                    "step": 3,
                    "instruction": "Retrieve published products.",
                    "query": "SELECT name FROM products WHERE published = 1;"
                }
            ],
            "assessment": {
                "question": "Which SQL statement retrieves information from a database?",
                "options": [
                    "DELETE",
                    "SELECT",
                    "DROP",
                    "INSERT"
                ]
            }
        })";
    }

    return R"({"error":"Lesson not implemented"})";
}