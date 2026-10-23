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

    // ====================================
  // Module 2: SQL Fundamentals
  // ====================================

    if (moduleId == 2)
    {
        return R"JSON({
            "id": 2,
            "title": "SQL Fundamentals",
            "difficulty": "Beginner",
            "estimated_minutes": 45,
            "description": "Learn to retrieve, filter, sort, and analyze relational data.",
            "sections": [
                {
                    "title": "Understanding SQL",
                    "content": "Structured Query Language (SQL) is used to interact with relational databases. SQL supports retrieving, inserting, updating, and deleting records."
                },
                {
                    "title": "SELECT and FROM",
                    "content": "SELECT specifies which columns to retrieve. FROM identifies the table. Example: SELECT name, price FROM products;"
                },
                {
                    "title": "Filtering with WHERE",
                    "content": "WHERE restricts the rows returned by a query. Example: SELECT name FROM products WHERE published = 1;"
                },
                {
                    "title": "Comparison Operators",
                    "content": "SQL supports operators such as =, <, >, <=, >=, and <>. Example: SELECT name FROM products WHERE price < 50;"
                },
                {
                    "title": "Logical Operators",
                    "content": "AND requires both conditions to be true. OR requires at least one condition to be true. Parentheses control evaluation order."
                },
                {
                    "title": "Sorting Results",
                    "content": "ORDER BY sorts query results. ASC sorts in ascending order and DESC sorts in descending order. Example: SELECT name, price FROM products ORDER BY price DESC;"
                },
                {
                    "title": "Limiting Results",
                    "content": "LIMIT restricts the number of rows returned. Example: SELECT name FROM products LIMIT 5;"
                },
                {
                    "title": "Aggregate Functions",
                    "content": "COUNT counts rows, SUM calculates totals, AVG calculates averages, and MIN and MAX identify extreme values."
                },
                {
                    "title": "NULL Values",
                    "content": "NULL represents a missing or unknown value. Use IS NULL or IS NOT NULL rather than comparing NULL with the equals operator."
                }
            ],
            "guided_practice": [
                {
                    "step": 1,
                    "instruction": "Retrieve all product names.",
                    "query": "SELECT name FROM products;"
                },
                {
                    "step": 2,
                    "instruction": "Retrieve published products.",
                    "query": "SELECT name FROM products WHERE published = 1;"
                },
                {
                    "step": 3,
                    "instruction": "Sort products by price.",
                    "query": "SELECT name, price FROM products ORDER BY price DESC;"
                },
                {
                    "step": 4,
                    "instruction": "Count the products.",
                    "query": "SELECT COUNT(*) FROM products;"
                }
            ],
            "assessment": {
                "question": "Which SQL clause filters rows based on a condition?",
                "options": [
                    "ORDER BY",
                    "WHERE",
                    "FROM",
                    "LIMIT"
                ],
                "correct_answer": 2,
                "explanation": "WHERE determines which rows satisfy a specified condition."
            }
        })JSON";
    }
    // ====================================
// Module 3: Understanding SQL Injection
// ====================================

    if (moduleId == 3)
    {
        return R"JSON({
            "id": 3,
            "title": "Understanding SQL Injection",
            "difficulty": "Beginner",
            "estimated_minutes": 45,
            "description": "Understand how unsafe SQL construction introduces security vulnerabilities.",
            "sections": [
                {
                    "title": "What Is SQL Injection?",
                    "content": "SQL injection occurs when untrusted input changes the structure or meaning of an SQL statement."
                },
                {
                    "title": "The Root Cause",
                    "content": "Applications become vulnerable when they combine untrusted values with SQL syntax instead of passing those values separately as parameters."
                },
                {
                    "title": "Unsafe Query Construction",
                    "content": "An application might construct a query by concatenating a username into SELECT * FROM users WHERE name = '...'. If the input is interpreted as SQL syntax, the intended condition can change."
                },
                {
                    "title": "Understanding Query Structure",
                    "content": "SQL statements contain keywords, operators, identifiers, and values. A secure application must prevent user-controlled values from changing the query structure."
                },
                {
                    "title": "Potential Consequences",
                    "content": "Depending on database permissions and application behavior, SQL injection may expose records, bypass application restrictions, or modify stored information."
                },
                {
                    "title": "Recognizing Risk",
                    "content": "User-controlled search fields, login forms, URL parameters, and API inputs can become injection points when applications construct SQL unsafely."
                },
                {
                    "title": "Ethical Testing",
                    "content": "Security testing requires explicit authorization. BugBountyTrainer uses isolated training databases containing fictional records."
                }
            ],
            "guided_practice": [
                {
                    "step": 1,
                    "instruction": "Identify the WHERE clause in a normal query.",
                    "query": "SELECT name FROM products WHERE published = 1;"
                },
                {
                    "step": 2,
                    "instruction": "Explain why combining SQL syntax with untrusted input is unsafe.",
                    "query": "SELECT name FROM products WHERE name = ?;"
                },
                {
                    "step": 3,
                    "instruction": "Compare a query with a bound parameter against one built through string concatenation.",
                    "query": "SELECT id, name FROM products WHERE name = ?;"
                }
            ],
            "assessment": {
                "question": "What is the fundamental cause of SQL injection?",
                "options": [
                    "Using SQLite",
                    "Storing records in tables",
                    "Allowing untrusted input to alter SQL structure",
                    "Using primary keys"
                ],
                "correct_answer": 3,
                "explanation": "SQL injection arises when user-controlled input changes the intended SQL statement."
            }
        })JSON";
    }
    // ====================================
// Module 4: Basic SQL Injection
// ====================================

    if (moduleId == 4)
    {
        return R"JSON({
            "id": 4,
            "title": "Basic SQL Injection",
            "difficulty": "Beginner",
            "estimated_minutes": 50,
            "description": "Explore query manipulation in a controlled SQL injection training environment.",
            "sections": [
                {
                    "title": "How Query Manipulation Works",
                    "content": "When an application inserts untrusted input directly into SQL syntax, the input may change the conditions used to retrieve records."
                },
                {
                    "title": "Boolean Conditions",
                    "content": "A WHERE clause evaluates conditions. Expressions involving AND and OR can affect which records satisfy the query."
                },
                {
                    "title": "Operator Precedence",
                    "content": "AND generally has higher precedence than OR. Parentheses make the intended grouping explicit."
                },
                {
                    "title": "Unsafe Search Queries",
                    "content": "A vulnerable product search may combine a user-supplied product name directly with an SQL statement. This can unintentionally alter filtering conditions."
                },
                {
                    "title": "Observing Unexpected Results",
                    "content": "In the local training lab, compare normal search results with results from intentionally unsafe query construction. Unexpected additional records indicate that the query logic may have changed."
                },
                {
                    "title": "Controlled Testing",
                    "content": "Use only BugBountyTrainer's fictional local database. Do not attempt these techniques against systems without authorization."
                },
                {
                    "title": "Documenting Findings",
                    "content": "A useful security report explains the affected input, expected behavior, observed behavior, potential impact, and recommended remediation."
                }
            ],
            "guided_practice": [
                {
                    "step": 1,
                    "instruction": "Observe the normal published-product filter.",
                    "query": "SELECT name FROM products WHERE published = 1;"
                },
                {
                    "step": 2,
                    "instruction": "Study how AND changes filtering behavior.",
                    "query": "SELECT name FROM products WHERE published = 1 AND price < 50;"
                },
                {
                    "step": 3,
                    "instruction": "Study how OR changes filtering behavior.",
                    "query": "SELECT name FROM products WHERE published = 1 OR price < 50;"
                },
                {
                    "step": 4,
                    "instruction": "Compare unsafe and parameterized search modes in the isolated Docker training lab.",
                    "query": "SELECT name FROM products WHERE name = ?;"
                }
            ],
            "assessment": {
                "question": "Why can unsafe SQL query construction return unintended records?",
                "options": [
                    "Because every database is public",
                    "Because untrusted input may change filtering conditions",
                    "Because SELECT always returns all rows",
                    "Because primary keys are optional"
                ],
                "correct_answer": 2,
                "explanation": "When input changes query logic, the database may evaluate different conditions than the developer intended."
            }
        })JSON";
    }
    // ====================================
// Module 5: Preventing SQL Injection
// ====================================

    if (moduleId == 5)
    {
        return R"JSON({
            "id": 5,
            "title": "Preventing SQL Injection",
            "difficulty": "Beginner",
            "estimated_minutes": 50,
            "description": "Learn secure query construction and database defense techniques.",
            "sections": [
                {
                    "title": "Parameterized Queries",
                    "content": "Parameterized queries separate SQL syntax from user-supplied values. This is the primary defense against SQL injection."
                },
                {
                    "title": "Prepared Statements",
                    "content": "A prepared statement defines the SQL structure before values are bound to placeholders."
                },
                {
                    "title": "SQLite Parameter Binding",
                    "content": "SQLite provides sqlite3_prepare_v2 for preparing statements and sqlite3_bind_text for binding text values. Applications must check return codes and release prepared statements."
                },
                {
                    "title": "Why Escaping Alone Is Insufficient",
                    "content": "Manually escaping characters is error-prone and depends on database-specific behavior. Parameter binding is generally safer."
                },
                {
                    "title": "Input Validation",
                    "content": "Input validation checks whether values satisfy application requirements. It complements parameterization but does not replace it."
                },
                {
                    "title": "Least Privilege",
                    "content": "Database accounts should have only the permissions required for their intended operations. This can reduce the impact of vulnerabilities."
                },
                {
                    "title": "Error Handling",
                    "content": "Applications should log useful diagnostic information securely while avoiding unnecessary disclosure of database internals to users."
                },
                {
                    "title": "Secure Development Testing",
                    "content": "Developers should test normal inputs, unexpected inputs, and error conditions. Security tests should verify that input is treated as data."
                }
            ],
            "guided_practice": [
                {
                    "step": 1,
                    "instruction": "Examine a parameterized product search.",
                    "query": "SELECT id, name FROM products WHERE name = ?;"
                },
                {
                    "step": 2,
                    "instruction": "Identify the placeholder that receives a bound value.",
                    "query": "SELECT name FROM products WHERE price < ?;"
                },
                {
                    "step": 3,
                    "instruction": "Compare the vulnerable and parameterized search modes in the local training website.",
                    "query": "SELECT name FROM products WHERE name = ? AND published = 1;"
                },
                {
                    "step": 4,
                    "instruction": "Explain why parameter binding prevents user input from becoming SQL syntax.",
                    "query": "SELECT name FROM products WHERE name = ?;"
                }
            ],
            "assessment": {
                "question": "Which approach most directly prevents SQL injection in database queries?",
                "options": [
                    "Hiding database errors",
                    "Using longer passwords",
                    "Using prepared statements with bound parameters",
                    "Renaming database tables"
                ],
                "correct_answer": 3,
                "explanation": "Prepared statements with bound parameters keep untrusted values separate from executable SQL syntax."
            }
        })JSON";
        // ====================================
// Module 6: SQL Query Manipulation
// ====================================

        if (moduleId == 6)
        {
            return R"JSON({
            "id": 6,
            "title": "SQL Query Manipulation",
            "difficulty": "Developing",
            "estimated_minutes": 50,
            "description": "Learn how SQL conditions, operators, and query structure affect database results.",
            "sections": [
                {
                    "title": "Understanding SQL Query Structure",
                    "content": "SQL queries use clauses such as SELECT, FROM, WHERE, GROUP BY, HAVING, and ORDER BY. Each clause controls how information is retrieved or organized."
                },
                {
                    "title": "Boolean Expressions",
                    "content": "SQL conditions use AND, OR, and NOT to combine logical expressions. These operators determine which records satisfy a query."
                },
                {
                    "title": "Operator Precedence",
                    "content": "AND generally has higher precedence than OR. Parentheses allow developers to control the order in which conditions are evaluated."
                },
                {
                    "title": "Query Manipulation",
                    "content": "When an application constructs SQL statements using untrusted input, that input may change the intended query conditions."
                },
                {
                    "title": "Unexpected Query Results",
                    "content": "A query that returns more records than expected may indicate incorrect filtering logic or unsafe query construction."
                },
                {
                    "title": "Secure Query Construction",
                    "content": "Parameterized queries keep user-supplied values separate from SQL syntax and prevent those values from changing query structure."
                }
            ],
            "guided_practice": [
                {
                    "step": 1,
                    "instruction": "Retrieve published products.",
                    "query": "SELECT name FROM products WHERE published = 1;"
                },
                {
                    "step": 2,
                    "instruction": "Combine filtering conditions using AND.",
                    "query": "SELECT name FROM products WHERE published = 1 AND price < 50;"
                },
                {
                    "step": 3,
                    "instruction": "Compare results using OR.",
                    "query": "SELECT name FROM products WHERE published = 1 OR price < 50;"
                },
                {
                    "step": 4,
                    "instruction": "Control evaluation order using parentheses.",
                    "query": "SELECT name FROM products WHERE (published = 1 OR price < 50) AND price > 10;"
                }
            ],
            "assessment": {
                "question": "Which SQL operator generally has higher precedence?",
                "options": [
                    "OR",
                    "AND",
                    "Both always have equal precedence",
                    "Neither"
                ],
                "correct_answer": 2,
                "explanation": "AND generally has higher precedence than OR."
            }
        })JSON";
        }

        // ====================================
        // Module 7: UNION-Based SQL Injection
        // ====================================

        if (moduleId == 7)
        {
            return R"JSON({
            "id": 7,
            "title": "UNION-Based SQL Injection",
            "difficulty": "Developing",
            "estimated_minutes": 55,
            "description": "Understand UNION queries and how unsafe SQL construction may expose unintended information.",
            "sections": [
                {
                    "title": "Understanding UNION",
                    "content": "The UNION operator combines the results of two SELECT statements into one result set."
                },
                {
                    "title": "UNION Requirements",
                    "content": "Both SELECT statements must return the same number of columns, and corresponding columns must contain compatible data types."
                },
                {
                    "title": "UNION vs UNION ALL",
                    "content": "UNION removes duplicate rows from combined results. UNION ALL retains duplicate rows."
                },
                {
                    "title": "UNION-Based SQL Injection",
                    "content": "When an application constructs SQL unsafely, untrusted input may alter a SELECT statement and potentially combine unintended query results."
                },
                {
                    "title": "Potential Security Impact",
                    "content": "Depending on database permissions, unintended UNION queries may expose records that an application was not designed to display."
                },
                {
                    "title": "Defensive Controls",
                    "content": "Prepared statements, parameter binding, least-privilege database permissions, and secure error handling help reduce SQL injection risks."
                }
            ],
            "guided_practice": [
                {
                    "step": 1,
                    "instruction": "Combine two fictional product result sets.",
                    "query": "SELECT name FROM products WHERE published = 1 UNION SELECT name FROM products WHERE price < 20;"
                },
                {
                    "step": 2,
                    "instruction": "Compare UNION with UNION ALL.",
                    "query": "SELECT name FROM products WHERE published = 1 UNION ALL SELECT name FROM products WHERE price < 20;"
                },
                {
                    "step": 3,
                    "instruction": "Examine compatible result columns.",
                    "query": "SELECT name, price FROM products UNION SELECT name, price FROM products;"
                }
            ],
            "assessment": {
                "question": "What does SQL UNION do?",
                "options": [
                    "Deletes duplicate tables",
                    "Combines compatible SELECT result sets",
                    "Encrypts database records",
                    "Changes database permissions"
                ],
                "correct_answer": 2,
                "explanation": "UNION combines compatible SELECT query results and removes duplicate rows."
            }
        })JSON";
        }

        // ====================================
        // Module 8: Database Enumeration
        // ====================================

        if (moduleId == 8)
        {
            return R"JSON({
            "id": 8,
            "title": "Database Enumeration",
            "difficulty": "Developing",
            "estimated_minutes": 55,
            "description": "Explore relational database schemas, tables, columns, and metadata.",
            "sections": [
                {
                    "title": "Understanding Database Schemas",
                    "content": "A database schema describes how information is organized, including tables, columns, constraints, and relationships."
                },
                {
                    "title": "Database Metadata",
                    "content": "Metadata describes database objects rather than the application records stored inside them."
                },
                {
                    "title": "SQLite Schema Information",
                    "content": "SQLite provides the sqlite_schema table, which contains information about tables, indexes, views, and triggers."
                },
                {
                    "title": "Inspecting Table Structures",
                    "content": "SQLite supports PRAGMA table_info, which displays column names, types, and other information about a specified table."
                },
                {
                    "title": "Security Considerations",
                    "content": "Exposing unnecessary database structure information can reveal details about an application's internal design."
                },
                {
                    "title": "Protecting Database Information",
                    "content": "Applications should restrict database access, use least-privilege permissions, and avoid disclosing unnecessary schema details."
                }
            ],
            "guided_practice": [
                {
                    "step": 1,
                    "instruction": "List tables in the fictional SQLite database.",
                    "query": "SELECT name, type FROM sqlite_schema WHERE type = 'table';"
                },
                {
                    "step": 2,
                    "instruction": "Inspect the products table structure.",
                    "query": "PRAGMA table_info(products);"
                },
                {
                    "step": 3,
                    "instruction": "Retrieve selected product columns.",
                    "query": "SELECT id, name, price FROM products;"
                }
            ],
            "assessment": {
                "question": "What information does a relational database schema describe?",
                "options": [
                    "Only database passwords",
                    "Tables, columns, constraints, and relationships",
                    "Only application source code",
                    "Network connection speeds"
                ],
                "correct_answer": 2,
                "explanation": "A relational database schema defines the structure and relationships of database objects."
            }
        })JSON";
        }

        // ====================================
        // Module 9: Authentication Vulnerabilities
        // ====================================

        if (moduleId == 9)
        {
            return R"JSON({
            "id": 9,
            "title": "Authentication Vulnerabilities",
            "difficulty": "Intermediate",
            "estimated_minutes": 60,
            "description": "Understand how insecure database queries can affect authentication systems.",
            "sections": [
                {
                    "title": "Authentication Fundamentals",
                    "content": "Authentication verifies a user's identity. Authorization determines which resources that user is permitted to access."
                },
                {
                    "title": "Database-Backed Authentication",
                    "content": "Applications often use databases to store account information and retrieve records during authentication."
                },
                {
                    "title": "Authentication and SQL Injection",
                    "content": "Unsafe SQL queries in authentication workflows may allow untrusted input to change the conditions used by the application."
                },
                {
                    "title": "Authentication Bypass Risks",
                    "content": "If authentication logic depends on unsafe query construction, unintended query results may undermine the application's identity checks."
                },
                {
                    "title": "Secure Password Storage",
                    "content": "Passwords should be protected using established password-hashing algorithms rather than stored as plaintext."
                },
                {
                    "title": "Secure Authentication Design",
                    "content": "Use parameterized queries, secure password verification, appropriate rate limiting, and consistent error messages."
                },
                {
                    "title": "Ethical Security Testing",
                    "content": "Authentication testing must be performed only against applications you own or have explicit authorization to assess."
                }
            ],
            "guided_practice": [
                {
                    "step": 1,
                    "instruction": "Study a parameterized account lookup. This is an illustrative query; the current products-only training database may not contain a users table.",
                    "query": "SELECT id, username FROM users WHERE username = ?;"
                },
                {
                    "step": 2,
                    "instruction": "Identify the placeholder used to bind an account identifier.",
                    "query": "SELECT id FROM users WHERE username = ?;"
                },
                {
                    "step": 3,
                    "instruction": "Explain the difference between authentication and authorization.",
                    "query": "SELECT id, username FROM users WHERE id = ?;"
                }
            ],
            "assessment": {
                "question": "Which practice helps protect database-backed authentication?",
                "options": [
                    "Store plaintext passwords",
                    "Construct SQL using string concatenation",
                    "Use parameterized queries and secure password hashing",
                    "Display detailed database errors"
                ],
                "correct_answer": 3,
                "explanation": "Parameterized queries protect SQL structure, while secure password hashing protects stored credentials."
            }
        })JSON";
        }
    }


                return R"({"error":"Lesson not implemented"})";
}