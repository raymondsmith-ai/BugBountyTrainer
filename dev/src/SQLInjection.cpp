#include "../include/SQLInjection.h"

#include <limits>

// ====================================
// SQL Injection Fundamentals Lesson
// ====================================

void SQLInjection::DisplayLesson() const
{
    std::cout << "\n====================================\n";
    std::cout << "     SQL INJECTION FUNDAMENTALS\n";
    std::cout << "====================================\n";

    std::cout << R"(

LESSON 1: WHAT IS SQL INJECTION?

SQL injection (SQLi) is a vulnerability
that occurs when untrusted input changes
the structure or behavior of an SQL query.

SQL injection typically occurs when an
application builds SQL statements by
combining SQL syntax with user input.

------------------------------------
LESSON 2: HOW SQL INJECTION OCCURS
------------------------------------

Consider an application that searches
for a user by username.

An unsafe C++ implementation might use:

std::string sql =
    "SELECT * FROM users WHERE name = '"
    + username + "'";

The application inserts the username
directly into the SQL statement.

If the username contains SQL syntax,
the resulting query may behave
differently than intended.

This can cause unauthorized records
to be returned or security checks
to be bypassed.

------------------------------------
LESSON 3: UNDERSTANDING QUERY LOGIC
------------------------------------

A normal SQL query might look like:

SELECT * FROM users
WHERE name = 'student';

The WHERE clause limits which records
are returned.

SQL injection can occur when user input
changes the intended WHERE condition.

In BugBountyTrainer, we demonstrate
this using fictional product records
inside an isolated Docker lab.

------------------------------------
LESSON 4: PARAMETERIZED QUERIES
------------------------------------

The primary defense against SQL injection
is to use parameterized queries.

Example:

SELECT * FROM users WHERE name = ?

The question mark is a placeholder.

The application binds the username as
a value instead of inserting it directly
into SQL syntax.

SQLite C++ example:

sqlite3_stmt* statement = nullptr;

sqlite3_prepare_v2(
    database,
    "SELECT * FROM users WHERE name = ?",
    -1,
    &statement,
    nullptr);

sqlite3_bind_text(
    statement,
    1,
    username.c_str(),
    -1,
    SQLITE_TRANSIENT);

sqlite3_step(statement);
sqlite3_finalize(statement);

The username is treated as data,
not executable SQL syntax.

Production applications must also
check SQLite return codes and handle
database errors appropriately.

------------------------------------
LESSON 5: ADDITIONAL DEFENSES
------------------------------------

1. Use prepared statements.

2. Apply least-privilege permissions
   to database accounts.

3. Validate input according to
   application requirements.

4. Avoid displaying detailed database
   errors to end users.

5. Keep database software updated.

6. Test only applications you own
   or have explicit authorization
   to assess.

------------------------------------
LESSON 6: HANDS-ON PRACTICE
------------------------------------

BugBountyTrainer includes a local
Docker SQL injection training lab.

The lab uses fictional records.

Students can compare:

- Unsafe SQL query construction
- Parameterized SQL queries
- Intended query results
- Unexpected query behavior

The purpose is to understand why
SQL injection occurs and how secure
query construction prevents it.

------------------------------------
LESSON SUMMARY
------------------------------------

SQL injection occurs when untrusted
input changes SQL query structure.

Parameterized queries separate
SQL syntax from user-supplied values.

Secure database permissions and
proper error handling provide
additional protection.

)";
}

// ====================================
// SQL Injection Assessment
// ====================================

bool SQLInjection::RunAssessment()
{
    int score = 0;

    const std::string questions[3] =
    {
        "What is the main cause of SQL injection?",
        "Which technique helps prevent SQL injection?",
        "How should untrusted input be handled?"
    };

    const std::string options[3][3] =
    {
        {
            "1. Using parameterized queries",
            "2. Combining untrusted input with SQL syntax",
            "3. Restricting database permissions"
        },
        {
            "1. String concatenation",
            "2. Parameterized queries",
            "3. Displaying detailed database errors"
        },
        {
            "1. Insert it directly into SQL statements",
            "2. Treat it as executable SQL",
            "3. Handle it as data"
        }
    };

    const int correctAnswers[3] = { 2, 2, 3 };

    std::cout << "\n====================================\n";
    std::cout << "      SQL INJECTION ASSESSMENT\n";
    std::cout << "====================================\n";

    for (int i = 0; i < 3; ++i)
    {
        std::cout << "\nQuestion " << (i + 1)
            << ": " << questions[i] << "\n\n";

        for (int j = 0; j < 3; ++j)
        {
            std::cout << options[i][j] << '\n';
        }

        int answer = 0;

        while (true)
        {
            std::cout << "\nAnswer (1-3): ";

            if (!(std::cin >> answer))
            {
                std::cin.clear();

                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(),
                    '\n');

                std::cout << "Invalid input. Enter 1, 2, or 3.\n";
                continue;
            }

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');

            if (answer >= 1 && answer <= 3)
            {
                break;
            }

            std::cout << "Enter a number between 1 and 3.\n";
        }

        if (answer == correctAnswers[i])
        {
            ++score;
            std::cout << "Correct!\n";
        }
        else
        {
            std::cout << "Incorrect.\n";
        }
    }

    std::cout << "\nAssessment Score: "
        << score << "/3\n";

    if (score == 3)
    {
        std::cout << "\nASSESSMENT PASSED!\n";
        return true;
    }

    std::cout << "\nAssessment not passed.\n";
    std::cout << "Review the lesson and try again.\n";

    return false;
}

// ====================================
// SQL Injection Training Menu
// ====================================

void SQLInjection::Run()
{
    bool running = true;

    while (running)
    {
        std::cout << "\n====================================\n";
        std::cout << "       SQL INJECTION TRAINING\n";
        std::cout << "====================================\n";

        std::cout << "Lesson: "
            << (lessonComplete ? "Completed" : "Not completed")
            << '\n';

        std::cout << "Assessment: "
            << (assessmentComplete ? "Passed" : "Not passed")
            << '\n';

        std::cout << "XP Reward: "
            << (rewardClaimed ? "Claimed" : "Not claimed")
            << '\n';

        std::cout << "\n1. Read SQL Injection Lesson\n";
        std::cout << "2. Take Assessment\n";
        std::cout << "0. Return to Main Menu\n";

        std::cout << "\nChoice: ";

        int choice = -1;

        if (!(std::cin >> choice))
        {
            std::cin.clear();

            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');

            std::cout << "Invalid selection.\n";
            continue;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');

        switch (choice)
        {
        case 1:
            DisplayLesson();
            lessonComplete = true;
            break;

        case 2:
            if (!lessonComplete)
            {
                std::cout << "\nComplete the lesson first.\n";
            }
            else if (assessmentComplete)
            {
                std::cout << "\nAssessment already passed.\n";
            }
            else
            {
                assessmentComplete = RunAssessment();
            }
            break;

        case 0:
            running = false;
            break;

        default:
            std::cout << "\nInvalid selection.\n";
            break;
        }
    }
}

// ====================================
// Progress Tracking
// ====================================

bool SQLInjection::IsLessonComplete() const
{
    return lessonComplete;
}

bool SQLInjection::IsAssessmentComplete() const
{
    return assessmentComplete;
}

bool SQLInjection::IsRewardClaimed() const
{
    return rewardClaimed;
}

void SQLInjection::MarkRewardClaimed()
{
    if (assessmentComplete)
    {
        rewardClaimed = true;
    }
}

void SQLInjection::RestoreProgress(
    bool lesson,
    bool assessment,
    bool reward)
{
    lessonComplete = lesson;
    assessmentComplete = lesson && assessment;
    rewardClaimed = assessmentComplete && reward;
}