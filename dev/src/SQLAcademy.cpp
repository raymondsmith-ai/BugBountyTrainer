#include "../include/SQLAcademy.h"

#include <iostream>
#include <limits>
#include <string>
#include <vector>

// ====================================
// SQL Academy Constructor
// ====================================

SQLAcademy::SQLAcademy()
{
    InitializeLessons();
}

// ====================================
// Initialize Curriculum
// ====================================

void SQLAcademy::InitializeLessons()
{
    lessons.clear();
    LoadCurriculum();
}

// ====================================
// Load All 13 SQL Academy Modules
// ====================================

void SQLAcademy::LoadCurriculum()
{
    // ====================================
    // MODULE 1
    // Introduction to Databases
    // ====================================

    lessons.push_back({
        1,
        "Introduction to Databases",
        "Beginner",
        "Learn how relational databases organize and store information.",
        {
            {
                "What Is a Database?",
                "A database is an organized collection of information. "
                "Applications use databases to store, retrieve, and manage data."
            },
            {
                "Relational Databases",
                "Relational databases organize information into tables. "
                "Each table represents a collection of related records."
            },
            {
                "Rows and Columns",
                "Rows represent individual records. "
                "Columns represent attributes such as ID, name, or price."
            },
            {
                "Primary Keys",
                "A primary key uniquely identifies each record in a table."
            },
            {
                "Introduction to SQLite",
                "SQLite is a lightweight relational database engine. "
                "It is useful for learning SQL and building local applications."
            }
        },
        {
            {
                "Retrieve all records from a fictional products table.",
                "SELECT * FROM products;"
            },
            {
                "Retrieve specific columns.",
                "SELECT name, price FROM products;"
            },
            {
                "Retrieve a product by its identifier.",
                "SELECT * FROM products WHERE id = 1;"
            }
        },
        {
            {
                "What is a relational database table?",
                {
                    "A collection of related records",
                    "A programming language",
                    "A network protocol",
                    "An operating system"
                },
                1,
                "A relational table stores records organized into rows and columns."
            },
            {
                "What does a primary key do?",
                {
                    "Encrypts a database",
                    "Uniquely identifies a record",
                    "Deletes duplicate tables",
                    "Creates a network connection"
                },
                2,
                "A primary key uniquely identifies records in a table."
            }
        },
        100,
        false
        });

    // ====================================
    // MODULE 2
    // SQL Fundamentals
    // ====================================

    lessons.push_back({
        2,
        "SQL Fundamentals",
        "Beginner",
        "Learn essential SQL statements for retrieving and organizing data.",
        {
            {
                "Introduction to SQL",
                "Structured Query Language, or SQL, is used to interact "
                "with relational databases."
            },
            {
                "SELECT Statements",
                "SELECT retrieves data from one or more database tables."
            },
            {
                "WHERE Conditions",
                "WHERE filters records based on specified conditions."
            },
            {
                "ORDER BY",
                "ORDER BY sorts query results in ascending or descending order."
            },
            {
                "LIMIT",
                "LIMIT restricts the number of records returned by a query."
            },
            {
                "SQL Operators",
                "SQL supports comparison operators such as =, <, >, <=, >=, "
                "and <>."
            }
        },
        {
            {
                "Retrieve all product names.",
                "SELECT name FROM products;"
            },
            {
                "Retrieve products costing less than 50.",
                "SELECT name, price FROM products WHERE price < 50;"
            },
            {
                "Sort products by price.",
                "SELECT name, price FROM products ORDER BY price DESC;"
            },
            {
                "Retrieve the first three products.",
                "SELECT * FROM products LIMIT 3;"
            }
        },
        {
            {
                "Which SQL statement retrieves records?",
                {
                    "DELETE",
                    "SELECT",
                    "DROP",
                    "ALTER"
                },
                2,
                "SELECT retrieves records from a database."
            },
            {
                "Which clause filters query results?",
                {
                    "ORDER BY",
                    "LIMIT",
                    "WHERE",
                    "FROM"
                },
                3,
                "WHERE filters records using specified conditions."
            }
        },
        150,
        false
        });

    // ====================================
    // MODULE 3
    // Understanding SQL Injection
    // ====================================

    lessons.push_back({
        3,
        "Understanding SQL Injection",
        "Beginner",
        "Understand how unsafe SQL query construction creates vulnerabilities.",
        {
            {
                "What Is SQL Injection?",
                "SQL injection is a vulnerability that occurs when untrusted "
                "input changes the intended structure of a database query."
            },
            {
                "How SQL Injection Happens",
                "Applications become vulnerable when they combine user input "
                "directly with SQL statements instead of binding values safely."
            },
            {
                "Potential Security Impact",
                "SQL injection may expose information, bypass application "
                "controls, or modify database records depending on permissions."
            },
            {
                "Understanding Trust Boundaries",
                "User input must be treated as untrusted data rather than "
                "executable SQL syntax."
            },
            {
                "Ethical Security Testing",
                "Security testing must only be performed against systems "
                "you own or have explicit authorization to assess."
            }
        },
        {
            {
                "Study an unsafe query construction example.",
                "SELECT * FROM products WHERE name = 'user_input';"
            },
            {
                "Study a parameterized alternative.",
                "SELECT * FROM products WHERE name = ?;"
            }
        },
        {
            {
                "What is the primary cause of SQL injection?",
                {
                    "Using relational databases",
                    "Allowing untrusted input to alter SQL syntax",
                    "Using primary keys",
                    "Sorting query results"
                },
                2,
                "SQL injection occurs when untrusted input changes "
                "the intended SQL statement."
            },
            {
                "Where should SQL injection testing be performed?",
                {
                    "Any public website",
                    "Only authorized systems",
                    "Any database connected to the internet",
                    "Any application with a login page"
                },
                2,
                "Security testing requires ownership or explicit authorization."
            }
        },
        150,
        false
        });

    // ====================================
    // MODULE 4
    // Basic SQL Injection
    // ====================================

    lessons.push_back({
        4,
        "Basic SQL Injection",
        "Beginner",
        "Examine basic SQL injection concepts in controlled training environments.",
        {
            {
                "Understanding Vulnerable Queries",
                "A vulnerable query may combine untrusted input with SQL "
                "syntax using string concatenation."
            },
            {
                "SQL Conditions",
                "SQL queries use conditions to determine which records "
                "are returned."
            },
            {
                "Boolean Logic",
                "AND and OR operators influence how WHERE conditions "
                "are evaluated."
            },
            {
                "Unexpected Query Results",
                "Unsafe query construction may produce results that "
                "the application developer did not intend."
            },
            {
                "Recognizing Secure Alternatives",
                "Prepared statements prevent input values from being "
                "interpreted as SQL commands."
            }
        },
        {
            {
                "Examine a normal product lookup.",
                "SELECT * FROM products WHERE id = 1;"
            },
            {
                "Study the effect of a boolean condition.",
                "SELECT * FROM products WHERE id = 1 AND published = 1;"
            },
            {
                "Compare the result of an OR condition.",
                "SELECT * FROM products WHERE id = 1 OR published = 1;"
            }
        },
        {
            {
                "Which SQL operator requires both conditions to be true?",
                {
                    "OR",
                    "AND",
                    "NOT",
                    "UNION"
                },
                2,
                "AND requires both conditions to evaluate as true."
            },
            {
                "What is a safer alternative to SQL string concatenation?",
                {
                    "Prepared statements",
                    "Plaintext passwords",
                    "Detailed database errors",
                    "Removing all WHERE clauses"
                },
                1,
                "Prepared statements keep values separate from SQL syntax."
            }
        },
        175,
        false
        });

    // ====================================
    // MODULE 5
    // Preventing SQL Injection
    // ====================================

    lessons.push_back({
        5,
        "Preventing SQL Injection",
        "Beginner",
        "Learn secure coding practices that protect database applications.",
        {
            {
                "Prepared Statements",
                "Prepared statements separate SQL structure from "
                "user-supplied values."
            },
            {
                "Parameterized Queries",
                "Parameterized queries use placeholders that are bound "
                "to values through database APIs."
            },
            {
                "Input Validation",
                "Input validation checks whether supplied values meet "
                "application requirements."
            },
            {
                "Least Privilege",
                "Database accounts should have only the permissions "
                "required to perform their intended tasks."
            },
            {
                "Error Handling",
                "Applications should avoid exposing detailed database "
                "errors to end users."
            },
            {
                "Defense in Depth",
                "Secure applications combine parameterized queries, "
                "validation, access controls, and monitoring."
            }
        },
        {
            {
                "Study a parameterized product lookup.",
                "SELECT * FROM products WHERE id = ?;"
            },
            {
                "Study a parameterized category lookup.",
                "SELECT name FROM products WHERE category = ?;"
            }
        },
        {
            {
                "Which technique best separates SQL syntax from user input?",
                {
                    "String concatenation",
                    "Prepared statements",
                    "Verbose database errors",
                    "Plaintext storage"
                },
                2,
                "Prepared statements prevent bound values from "
                "changing SQL structure."
            },
            {
                "What does least privilege mean?",
                {
                    "Grant every permission",
                    "Remove authentication",
                    "Grant only necessary permissions",
                    "Disable logging"
                },
                3,
                "Least privilege limits access to required operations."
            }
        },
        175,
        false
        });

    // ====================================
    // MODULE 6
    // SQL Query Manipulation
    // ====================================

    lessons.push_back({
        6,
        "SQL Query Manipulation",
        "Developing",
        "Explore SQL conditions, operator precedence, and query behavior.",
        {
            {
                "Query Structure",
                "SQL queries combine clauses such as SELECT, FROM, "
                "WHERE, GROUP BY, and ORDER BY."
            },
            {
                "Boolean Expressions",
                "AND, OR, and NOT combine conditions to determine "
                "which records match."
            },
            {
                "Operator Precedence",
                "AND generally takes precedence over OR. "
                "Parentheses control evaluation order."
            },
            {
                "Query Manipulation Risks",
                "Unsafe query construction may allow untrusted input "
                "to change intended query conditions."
            },
            {
                "Defensive Query Construction",
                "Parameterized queries protect SQL structure "
                "from user-controlled values."
            }
        },
        {
            {
                "Combine two conditions.",
                "SELECT name FROM products WHERE published = 1 AND price < 50;"
            },
            {
                "Compare OR conditions.",
                "SELECT name FROM products WHERE published = 1 OR price < 50;"
            },
            {
                "Control operator precedence.",
                "SELECT name FROM products "
                "WHERE (published = 1 OR price < 50) AND price > 10;"
            }
        },
        {
            {
                "Which SQL operator generally has higher precedence?",
                {
                    "OR",
                    "AND",
                    "Both always have equal precedence",
                    "Neither"
                },
                2,
                "AND generally has higher precedence than OR."
            }
        },
        200,
        false
        });

    // ====================================
    // MODULE 7
    // UNION-Based SQL Injection
    // ====================================

    lessons.push_back({
        7,
        "UNION-Based SQL Injection",
        "Developing",
        "Understand UNION queries and their security implications.",
        {
            {
                "Understanding UNION",
                "UNION combines compatible SELECT query results "
                "into one result set."
            },
            {
                "Column Requirements",
                "Both SELECT statements must return the same number "
                "of columns with compatible data types."
            },
            {
                "UNION vs UNION ALL",
                "UNION removes duplicate rows. "
                "UNION ALL preserves duplicate rows."
            },
            {
                "UNION Injection Concepts",
                "Unsafe SQL construction may allow untrusted input "
                "to alter a query and combine unintended results."
            },
            {
                "Security Impact",
                "Unexpected query results may expose information "
                "that an application was not intended to display."
            },
            {
                "Prevention",
                "Prepared statements and least-privilege database "
                "access reduce injection risks."
            }
        },
        {
            {
                "Combine fictional product results.",
                "SELECT name FROM products WHERE published = 1 "
                "UNION SELECT name FROM products WHERE price < 20;"
            },
            {
                "Compare UNION ALL.",
                "SELECT name FROM products WHERE published = 1 "
                "UNION ALL SELECT name FROM products WHERE price < 20;"
            }
        },
        {
            {
                "What does SQL UNION do?",
                {
                    "Deletes tables",
                    "Combines compatible SELECT results",
                    "Encrypts records",
                    "Changes permissions"
                },
                2,
                "UNION combines compatible SELECT query results."
            }
        },
        225,
        false
        });

    // ====================================
    // MODULE 8
    // Database Enumeration
    // ====================================

    lessons.push_back({
        8,
        "Database Enumeration",
        "Developing",
        "Learn how database schemas organize tables, columns, and metadata.",
        {
            {
                "Database Schemas",
                "A schema defines tables, columns, constraints, "
                "and relationships."
            },
            {
                "Database Metadata",
                "Metadata describes database objects and structures."
            },
            {
                "SQLite Schema",
                "SQLite stores database structure information "
                "in sqlite_schema."
            },
            {
                "Table Inspection",
                "PRAGMA table_info displays information about "
                "a SQLite table's columns."
            },
            {
                "Security Considerations",
                "Unnecessary exposure of schema information "
                "may reveal application internals."
            },
            {
                "Least Privilege",
                "Database access should be restricted "
                "to required operations."
            }
        },
        {
            {
                "Inspect table names.",
                "SELECT name FROM sqlite_schema WHERE type = 'table';"
            },
            {
                "Inspect product columns.",
                "PRAGMA table_info(products);"
            },
            {
                "Retrieve selected columns.",
                "SELECT id, name, price FROM products;"
            }
        },
        {
            {
                "What does a relational database schema describe?",
                {
                    "Only passwords",
                    "Tables, columns, and relationships",
                    "Only source code",
                    "Network speed"
                },
                2,
                "A schema defines the structure of database objects."
            }
        },
        225,
        false
        });

    // ====================================
    // MODULE 9
    // Authentication Vulnerabilities
    // ====================================

    lessons.push_back({
        9,
        "Authentication Vulnerabilities",
        "Intermediate",
        "Learn how insecure database queries affect authentication systems.",
        {
            {
                "Authentication",
                "Authentication verifies the identity of a user."
            },
            {
                "Authorization",
                "Authorization determines which resources "
                "an authenticated user may access."
            },
            {
                "Database-Backed Authentication",
                "Applications often use databases to retrieve "
                "account information."
            },
            {
                "Authentication and SQL Injection",
                "Unsafe authentication queries may allow "
                "untrusted input to alter intended conditions."
            },
            {
                "Password Security",
                "Passwords should be protected using established "
                "password-hashing algorithms."
            },
            {
                "Secure Authentication Design",
                "Use parameterized queries, secure password verification, "
                "rate limiting, and appropriate error handling."
            }
        },
        {
            {
                "Study a parameterized account lookup. "
                "This is illustrative and requires a users table.",
                "SELECT id, username FROM users WHERE username = ?;"
            },
            {
                "Study a parameterized account identifier lookup.",
                "SELECT id FROM users WHERE id = ?;"
            }
        },
        {
            {
                "What is authentication?",
                {
                    "Assigning database permissions",
                    "Verifying a user's identity",
                    "Encrypting every database table",
                    "Sorting account records"
                },
                2,
                "Authentication verifies identity."
            },
            {
                "Which approach helps secure database-backed authentication?",
                {
                    "Plaintext passwords",
                    "SQL string concatenation",
                    "Parameterized queries and secure password hashing",
                    "Displaying detailed database errors"
                },
                3,
                "Parameterized queries and secure password hashing "
                "protect authentication systems."
            }
        },
        250,
        false
        });

    // ====================================
    // MODULE 10
    // Error-Based SQL Injection
    // ====================================

    lessons.push_back({
        10,
        "Error-Based SQL Injection",
        "Intermediate",
        "Understand how database errors can reveal application information.",
        {
            {
                "Database Errors",
                "Database engines produce errors when SQL statements "
                "contain invalid syntax or unsupported operations."
            },
            {
                "Information Disclosure",
                "Detailed database errors may reveal table names, "
                "column names, query structure, or implementation details."
            },
            {
                "Error-Based Injection Concepts",
                "When unsafe queries expose database errors, "
                "those messages may reveal information about "
                "how an application interacts with its database."
            },
            {
                "Secure Error Handling",
                "Applications should display generic error messages "
                "while recording appropriate diagnostic details "
                "in protected server logs."
            },
            {
                "Defensive Testing",
                "Developers should verify that malformed input "
                "does not expose sensitive database information."
            }
        },
        {
            {
                "Inspect a valid query.",
                "SELECT name FROM products;"
            },
            {
                "Compare with a query referencing a missing column.",
                "SELECT nonexistent_column FROM products;"
            },
            {
                "Discuss how an application should handle "
                "the resulting database error.",
                "SELECT name FROM products WHERE id = ?;"
            }
        },
        {
            {
                "Why can detailed database errors be a security risk?",
                {
                    "They automatically encrypt records",
                    "They may expose internal database information",
                    "They prevent all SQL queries",
                    "They remove database permissions"
                },
                2,
                "Detailed errors can reveal information about "
                "database structure and application behavior."
            }
        },
        250,
        false
        });

    // ====================================
    // MODULE 11
    // Blind SQL Injection
    // ====================================

    lessons.push_back({
        11,
        "Blind SQL Injection",
        "Intermediate",
        "Understand how applications may reveal query behavior indirectly.",
        {
            {
                "Understanding Blind SQL Injection",
                "Blind SQL injection refers to situations where "
                "an application does not directly display database "
                "results or detailed errors."
            },
            {
                "Boolean-Based Behavior",
                "Different application responses may indicate "
                "whether a database condition evaluated as true or false."
            },
            {
                "Time-Based Behavior",
                "Some database operations may affect response timing. "
                "Timing observations require careful interpretation."
            },
            {
                "Limitations of Observations",
                "Network delays, caching, and server load can affect "
                "responses and produce misleading results."
            },
            {
                "Defensive Controls",
                "Parameterized queries, least privilege, "
                "monitoring, and secure error handling help "
                "protect applications."
            }
        },
        {
            {
                "Compare a true condition in a local training query.",
                "SELECT name FROM products WHERE 1 = 1;"
            },
            {
                "Compare a false condition.",
                "SELECT name FROM products WHERE 1 = 0;"
            },
            {
                "Explain why different result sets do not "
                "automatically establish a vulnerability.",
                "SELECT name FROM products WHERE published = 1;"
            }
        },
        {
            {
                "What characterizes blind SQL injection?",
                {
                    "Database results are always displayed",
                    "Information may be inferred from indirect application behavior",
                    "The database contains no tables",
                    "SQL queries cannot use conditions"
                },
                2,
                "Blind SQL injection involves indirect observations "
                "rather than direct display of database results."
            }
        },
        275,
        false
        });

    // ====================================
    // MODULE 12
    // Secure Database Development
    // ====================================

    lessons.push_back({
        12,
        "Secure Database Development",
        "Intermediate",
        "Apply defensive programming principles to database applications.",
        {
            {
                "Secure Database Architecture",
                "Applications should separate database access "
                "logic from presentation and user input handling."
            },
            {
                "Parameterized Queries",
                "Use prepared statements and bound parameters "
                "instead of concatenating untrusted input into SQL."
            },
            {
                "Input Validation",
                "Validate data types, lengths, ranges, and formats "
                "according to application requirements."
            },
            {
                "Least-Privilege Access",
                "Database accounts should receive only the permissions "
                "required for their responsibilities."
            },
            {
                "Password Storage",
                "Use established password-hashing algorithms "
                "with appropriate configuration."
            },
            {
                "Secure Error Handling",
                "Avoid revealing internal database details "
                "through public error messages."
            },
            {
                "Security Testing",
                "Test expected and unexpected inputs in authorized "
                "development and training environments."
            }
        },
        {
            {
                "Study a parameterized product lookup.",
                "SELECT id, name FROM products WHERE id = ?;"
            },
            {
                "Study a parameterized category filter.",
                "SELECT name, price FROM products WHERE category = ?;"
            },
            {
                "Study a parameterized price range.",
                "SELECT name FROM products WHERE price BETWEEN ? AND ?;"
            }
        },
        {
            {
                "Which approach best prevents SQL injection?",
                {
                    "Concatenate user input into SQL",
                    "Use prepared statements with bound parameters",
                    "Display detailed SQL errors",
                    "Grant database administrator permissions"
                },
                2,
                "Prepared statements separate SQL structure "
                "from untrusted values."
            },
            {
                "What is defense in depth?",
                {
                    "Using only one security control",
                    "Disabling database access",
                    "Combining multiple complementary security controls",
                    "Removing application logging"
                },
                3,
                "Defense in depth combines controls to reduce risk."
            }
        },
        300,
        false
        });

    // ====================================
    // MODULE 13
    // Final Practical Assessment
    // ====================================

    lessons.push_back({
        13,
        "Final Practical Assessment",
        "Intermediate",
        "Demonstrate understanding of SQL, injection risks, and secure development.",
        {
            {
                "Final Assessment Overview",
                "This module reviews the SQL Academy curriculum. "
                "Complete the assessment to demonstrate your understanding."
            },
            {
                "SQL Fundamentals Review",
                "Review SELECT, WHERE, ORDER BY, comparison operators, "
                "and database structure."
            },
            {
                "SQL Injection Review",
                "Review how unsafe query construction can allow "
                "untrusted input to change SQL behavior."
            },
            {
                "Database Security Review",
                "Review parameterized queries, least privilege, "
                "secure error handling, and authentication security."
            },
            {
                "Ethical Testing Review",
                "Apply security concepts only within authorized "
                "training and testing environments."
            }
        },
        {
            {
                "Retrieve published products.",
                "SELECT name FROM products WHERE published = 1;"
            },
            {
                "Retrieve products below a price threshold.",
                "SELECT name, price FROM products WHERE price < 50;"
            },
            {
                "Inspect a safe parameterized query.",
                "SELECT id, name FROM products WHERE id = ?;"
            }
        },
        {
            {
                "Which SQL clause filters records?",
                {
                    "ORDER BY",
                    "WHERE",
                    "LIMIT",
                    "GROUP BY"
                },
                2,
                "WHERE filters records based on conditions."
            },
            {
                "What causes SQL injection?",
                {
                    "Using primary keys",
                    "Untrusted input changing SQL query structure",
                    "Using relational tables",
                    "Using SQLite"
                },
                2,
                "SQL injection occurs when untrusted input "
                "changes intended SQL syntax."
            },
            {
                "What does UNION do?",
                {
                    "Deletes database tables",
                    "Combines compatible SELECT results",
                    "Creates user accounts",
                    "Encrypts records"
                },
                2,
                "UNION combines compatible SELECT query results."
            },
            {
                "Which technique helps prevent SQL injection?",
                {
                    "String concatenation",
                    "Prepared statements",
                    "Detailed public database errors",
                    "Plaintext password storage"
                },
                2,
                "Prepared statements keep input values "
                "separate from SQL syntax."
            },
            {
                "What is the purpose of least privilege?",
                {
                    "Grant all users administrator access",
                    "Disable authentication",
                    "Restrict access to necessary permissions",
                    "Expose database metadata"
                },
                3,
                "Least privilege limits permissions "
                "to what is necessary."
            },
            {
                "What should developers do with detailed database errors?",
                {
                    "Display them to every user",
                    "Store appropriate diagnostics in protected logs",
                    "Disable all error handling",
                    "Include database credentials in messages"
                },
                2,
                "Detailed diagnostics belong in protected logs, "
                "not public application responses."
            }
        },
        500,
        false
        });
}

// ====================================
// Input Validation
// ====================================

int SQLAcademy::GetValidatedChoice(int min, int max) const
{
    int choice = min;
    bool valid = false;

    while (!valid)
    {
        std::cout << "\nChoice: ";

        if (std::cin >> choice && choice >= min && choice <= max)
        {
            valid = true;
        }
        else
        {
            std::cout << "\nInvalid choice. Try again.\n";
            std::cin.clear();
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');

        if (!valid)
        {
            std::cout << "Please enter a number from "
                << min << " to " << max << ".\n";
        }
    }

    return choice;
}

// ====================================
// Display SQL Academy Menu
// ====================================

void SQLAcademy::DisplayMenu() const
{
    std::cout << "\n====================================\n";
    std::cout << "             SQL ACADEMY\n";
    std::cout << "====================================\n";

    for (std::size_t i = 0; i < lessons.size(); ++i)
    {
        const SQLLesson& lesson = lessons[i];

        std::cout << lesson.id << ". ";

        if (lesson.completed)
        {
            std::cout << "[COMPLETED] ";
        }
        else if (IsLessonUnlocked(i))
        {
            std::cout << "[AVAILABLE] ";
        }
        else
        {
            std::cout << "[LOCKED] ";
        }

        std::cout << lesson.title << '\n';
    }

    std::cout << "\n0. Return to Main Menu\n";
    std::cout << "====================================\n";
}

// ====================================
// Check Lesson Unlock Status
// ====================================

bool SQLAcademy::IsLessonUnlocked(std::size_t lessonIndex) const
{
    bool unlocked = false;

    if (lessonIndex == 0 && !lessons.empty())
    {
        unlocked = true;
    }
    else if (lessonIndex < lessons.size())
    {
        unlocked = lessons[lessonIndex - 1].completed;
    }

    return unlocked;
}

// ====================================
// Display Lesson Content
// ====================================

void SQLAcademy::OpenLesson(std::size_t lessonIndex)
{
    if (lessonIndex >= lessons.size())
    {
        return;
    }

    const SQLLesson& lesson = lessons[lessonIndex];

    std::cout << "\n====================================\n";
    std::cout << lesson.title << '\n';
    std::cout << "Difficulty: " << lesson.difficulty << '\n';
    std::cout << "====================================\n";

    std::cout << lesson.description << "\n";

    for (const SQLLessonSection& section : lesson.sections)
    {
        std::cout << "\n--- " << section.title << " ---\n";
        std::cout << section.content << "\n";
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

// ====================================
// Guided SQL Practice
// ====================================

void SQLAcademy::RunGuidedPractice(std::size_t lessonIndex) const
{
    if (lessonIndex >= lessons.size())
    {
        return;
    }

    const SQLLesson& lesson = lessons[lessonIndex];

    std::cout << "\n====================================\n";
    std::cout << "          GUIDED PRACTICE\n";
    std::cout << "====================================\n";

    if (lesson.exercises.empty())
    {
        std::cout << "\nNo guided exercises available.\n";
    }

    for (std::size_t i = 0; i < lesson.exercises.size(); ++i)
    {
        std::cout << "\nExercise " << i + 1 << '\n';
        std::cout << lesson.exercises[i].instruction << '\n';

        std::cout << "\nExample SQL:\n";
        std::cout << lesson.exercises[i].exampleQuery << "\n";
    }

    std::cout << "\nThese are study examples. "
        << "They are not executed against the Docker database.\n";

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

// ====================================
// Run Lesson Assessment
// ====================================

void SQLAcademy::RunAssessment(std::size_t lessonIndex)
{
    if (lessonIndex >= lessons.size())
    {
        return;
    }

    SQLLesson& lesson = lessons[lessonIndex];

    if (lesson.completed)
    {
        std::cout << "\nYou already completed this module.\n";
        std::cout << "No additional XP is available.\n";
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
        return;
    }

    if (lesson.questions.empty())
    {
        std::cout << "\nNo assessment available.\n";
        std::cout << "\nPress Enter to continue...";
        std::cin.get();
        return;
    }

    int correct = 0;

    for (std::size_t i = 0; i < lesson.questions.size(); ++i)
    {
        const SQLQuestion& question = lesson.questions[i];

        std::cout << "\n------------------------------------\n";
        std::cout << "Question " << i + 1
            << " of " << lesson.questions.size() << '\n';
        std::cout << "------------------------------------\n";

        std::cout << question.question << "\n\n";

        for (std::size_t j = 0; j < question.options.size(); ++j)
        {
            std::cout << j + 1 << ". "
                << question.options[j] << '\n';
        }

        int answer = GetValidatedChoice(
            1,
            static_cast<int>(question.options.size()));

        if (answer == question.correctAnswer)
        {
            ++correct;
            std::cout << "\nCorrect!\n";
        }
        else
        {
            std::cout << "\nIncorrect.\n";
        }

        std::cout << question.explanation << '\n';
    }

    std::cout << "\n====================================\n";
    std::cout << "          ASSESSMENT RESULTS\n";
    std::cout << "====================================\n";

    std::cout << "Score: " << correct
        << "/" << lesson.questions.size() << '\n';

    if (correct == static_cast<int>(lesson.questions.size()))
    {
        lesson.completed = true;

        std::cout << "\nASSESSMENT PASSED!\n";
        std::cout << "Module Completed: " << lesson.title << '\n';
        std::cout << "Configured XP Reward: "
            << lesson.xpReward << " XP\n";
        std::cout << "Researcher XP integration is pending.\n";

        if (lessonIndex + 1 < lessons.size())
        {
            std::cout << "\nNext module unlocked: "
                << lessons[lessonIndex + 1].title << '\n';
        }
        else
        {
            std::cout << "\nCONGRATULATIONS!\n";
            std::cout << "You completed all 13 SQL Academy modules!\n";
        }
    }
    else
    {
        std::cout << "\nAssessment not passed.\n";
        std::cout << "Review the lesson and try again.\n";
    }

    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

// ====================================
// SQL Academy Main Loop
// ====================================

void SQLAcademy::Run()
{
    bool running = true;

    while (running)
    {
        DisplayMenu();

        int choice = GetValidatedChoice(
            0,
            static_cast<int>(lessons.size()));

        if (choice == 0)
        {
            running = false;
        }
        else
        {
            std::size_t index = static_cast<std::size_t>(choice - 1);

            if (!IsLessonUnlocked(index))
            {
                std::cout << "\n====================================\n";
                std::cout << "             MODULE LOCKED\n";
                std::cout << "====================================\n";
                std::cout << "Complete the previous module first.\n";

                std::cout << "\nPress Enter to continue...";
                std::cin.get();
            }
            else
            {
                bool inLesson = true;

                while (inLesson)
                {
                    std::cout << "\n====================================\n";
                    std::cout << lessons[index].title << '\n';
                    std::cout << "====================================\n";

                    std::cout << "1. Read Lesson\n";
                    std::cout << "2. Guided Practice\n";
                    std::cout << "3. Take Assessment\n";
                    std::cout << "0. Return to SQL Academy\n";

                    int lessonChoice = GetValidatedChoice(0, 3);

                    switch (lessonChoice)
                    {
                    case 1:
                        OpenLesson(index);
                        break;

                    case 2:
                        RunGuidedPractice(index);
                        break;

                    case 3:
                        RunAssessment(index);
                        break;

                    case 0:
                        inLesson = false;
                        break;

                    default:
                        break;
                    }
                }
            }
        }
    }
}

// ====================================
// Check Lesson Completion
// ====================================

bool SQLAcademy::IsLessonComplete(int lessonId) const
{
    bool complete = false;

    for (const SQLLesson& lesson : lessons)
    {
        if (lesson.id == lessonId)
        {
            complete = lesson.completed;
            break;
        }
    }

    return complete;
}

// ====================================
// Restore Saved Lesson Completion
// ====================================

void SQLAcademy::RestoreLessonCompletion(int lessonId, bool completed)
{
    for (SQLLesson& lesson : lessons)
    {
        if (lesson.id == lessonId)
        {
            lesson.completed = completed;
            break;
        }
    }
}

// ====================================
// Retrieve All Lessons
// ====================================

const std::vector<SQLLesson>& SQLAcademy::GetLessons() const
{
    return lessons;
}