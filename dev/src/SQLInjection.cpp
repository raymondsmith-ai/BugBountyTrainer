#include "../include/SQLInjection.h"

#include <limits>

// ====================================
// SQL Injection Fundamentals
// ====================================

void SQLInjection::DisplayLesson() const
{
    std::cout << "\n====================================\n";
    std::cout << "     SQL INJECTION FUNDAMENTALS\n";
    std::cout << "====================================\n";

    std::cout << R"(

WHAT IS SQL INJECTION?

SQL injection is a security vulnerability
that occurs when an application allows
untrusted input to alter an SQL query.

HOW DOES IT HAPPEN?

An application may construct SQL queries
by combining SQL statements with user input.

If the input is not handled securely,
it may change the intended query logic.

EXAMPLE OF UNSAFE CODE:

std::string sql =
    "SELECT * FROM users WHERE name = '"
    + username + "'";

This example builds a query through
string concatenation.

WHY IS THIS DANGEROUS?

Depending on the application, SQL injection
may allow unauthorized access to records,
bypass intended filtering, or expose data.

HOW DO WE PREVENT IT?

Use parameterized queries.

EXAMPLE:

SELECT * FROM users WHERE name = ?

The question mark represents a bound value.

The database treats the supplied value as
data rather than executable SQL syntax.

OTHER SECURITY PRACTICES:

1. Apply least-privilege database permissions.
2. Validate input according to business rules.
3. Avoid exposing detailed database errors.
4. Test only systems you own or are authorized
   to assess.

HANDS-ON PRACTICE:

BugBountyTrainer provides a local Docker
environment with fictional product records.

The lab demonstrates the difference between
unsafe SQL construction and parameterized
queries.

)";
}

// ====================================
// SQL Injection Assessment
// ====================================

bool SQLInjection::RunAssessment()
{
    int answer = 0;
    int score = 0;

    std::cout << "\n====================================\n";
    std::cout << "      SQL INJECTION ASSESSMENT\n";
    std::cout << "====================================\n";

    const std::string questions[3] =
    {
        "What is the main cause of SQL injection?",
        "Which technique helps prevent SQL injection?",
        "What should happen to untrusted input?"
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
            "3. Displaying database errors"
        },
        {
            "1. Be inserted directly into SQL statements",
            "2. Be treated as executable SQL",
            "3. Be handled as data"
        }
    };

    const int correctAnswers[3] = { 2, 2, 3 };

    for (int i = 0; i < 3; i++)
    {
        std::cout << "\n" << questions[i] << "\n\n";

        for (int j = 0; j < 3; j++)
        {
            std::cout << options[i][j] << '\n';
        }

        std::cout << "\nAnswer: ";

        if (!(std::cin >> answer))
        {
            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(),
                '\n');

            std::cout << "Invalid input.\n";
            return false;
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n');

        if (answer == correctAnswers[i])
        {
            score++;
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
// SQL Injection Menu
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