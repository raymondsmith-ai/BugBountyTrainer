#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// Query-reading lessons only. This class does not execute SQL.
// Docker provides the separate environment for database exercises.
class SQLFundamentals
{
private:
    bool guidedComplete = false;
    bool assessmentComplete = false;
    bool rewardClaimed = false;

    struct Exercise
    {
        std::string query;
        std::string prompt;
        std::string answer;
        std::string hint;
        std::string explanation;
    };

    static std::string Read(std::istream& input)
    {
        std::string line;

        if (!std::getline(input, line))
        {
            throw std::runtime_error("Input stream closed.");
        }

        const auto begin = line.find_first_not_of(" \t\r");
        const auto end = line.find_last_not_of(" \t\r");

        return begin == std::string::npos
            ? ""
            : line.substr(begin, end - begin + 1);
    }

    static void Lesson(std::ostream& output)
    {
        output << R"(
SQL FUNDAMENTALS - STAGE 1
Where: C++ trainer. No database commands are executed on this screen.
Goal: read a SELECT query and predict which fictional records it returns.

1. TABLES AND ROWS
A database organizes related records in tables. A row is one record; columns
describe its fields. A schema defines those fields and their types.
In the products table, name is text, price is numeric, and published uses
1 for visible products and 0 for hidden products in this particular schema.

2. SELECT AND FROM
SELECT name, price FROM products;
SELECT chooses the output columns. FROM chooses the table.
This statement reads data; it does not change product records.

3. WHERE
SELECT name FROM products WHERE published = 1;
WHERE keeps only rows for which the condition is true. A numeric comparison
such as price < 30 excludes a product priced at exactly 30.
SQL text values use single quotes, for example name = 'Training Notebook'.

4. AND, OR, AND PARENTHESES
AND requires both conditions to be true. OR requires at least one.
AND binds more tightly than OR. Parentheses make the intended grouping clear:
(category = 'Hardware' OR category = 'Books') AND published = 1
filters both categories to published records.

5. REQUEST TO DATABASE
A browser sends an HTTP request. Application code reads the input and builds
or binds a database query. SQL injection happens when untrusted input can
change SQL structure. A bound parameter passes a value separately from SQL.
Example template: SELECT name FROM products WHERE name = ? AND published = 1;
The question mark is a SQLite value placeholder, not text concatenation.

6. SCOPE OF THIS STAGE
Here you practice reasoning about queries. The Docker website runs real SQLite
queries. The existing website demonstrates a filtering bypass and its defense;
it does not yet contain the full SQL injection course or verify Burp usage.

7. SAVING PROGRESS
Guided practice and assessment completion are included when you choose
Save Progress from the main menu. This lesson does not automatically save.
Passing earns a one-time 150 XP reward when returning to the main menu.
This assessment does not complete an external lab.
)";
    }

    bool Guided(std::istream& input, std::ostream& output)
    {
        output << R"(
GUIDED WORKSHEET - use this fictional products table
ID | Name              | Price | Published
1  | Training Notebook | 12    | 1
2  | Practice Keyboard | 35    | 1
3  | Hidden Adapter    | 20    | 0

Enter a row count, 'hint' for help, or 'back' to leave.
You must solve all three exercises in this visit to finish guided practice.
)";

        const std::vector<Exercise> exercises =
        {
            {
                "SELECT name FROM products;",
                "How many rows are returned?",
                "3",
                "There is no WHERE condition to exclude any row.",
                "All three rows qualify. Selecting fewer columns does not remove rows."
            },
            {
                "SELECT name FROM products WHERE published = 1 AND price < 30;",
                "How many rows are returned?",
                "1",
                "Check published AND price for every row. Both must be true.",
                "Only Training Notebook qualifies. Keyboard costs 35; Adapter is hidden."
            },
            {
                "SELECT name FROM products WHERE published = 1 OR price < 30;",
                "How many rows are returned?",
                "3",
                "OR includes a row when either condition is true.",
                "The two published products qualify, and the hidden Adapter costs under 30."
            }
        };

        bool finished = true;

        for (const Exercise& exercise : exercises)
        {
            bool solved = false;

            while (!solved && finished)
            {
                output << '\n' << exercise.query << '\n'
                    << exercise.prompt << "\nAnswer: ";

                const std::string answer = Read(input);

                if (answer == "back")
                {
                    finished = false;
                }
                else if (answer == "hint")
                {
                    output << "Hint: " << exercise.hint << '\n';
                }
                else if (answer == exercise.answer)
                {
                    solved = true;
                    output << "Correct. " << exercise.explanation << '\n';
                }
                else
                {
                    output << "Not yet. Recheck each row, or type hint. "
                        << "No XP is changed.\n";
                }
            }

            if (!finished)
            {
                break;
            }
        }

        if (finished)
        {
            output << "\nGuided practice complete!\n"
                << "Save from the main menu to keep this progress.\n";
        }

        return finished;
    }

    bool Assess(std::istream& input, std::ostream& output)
    {
        output << R"(
INDEPENDENT QUERY CHALLENGE - new fictional inventory table
ID | Name        | Category | Price | Published
1  | Cable       | Tools    | 15    | 1
2  | Toolkit     | Tools    | 40    | 1
3  | Hidden Kit  | Tools    | 25    | 0
4  | SQL Guide   | Books    | 20    | 1
5  | Lab Manual  | Books    | 60    | 0

Predict results without hints. Enter a number or 'back' to leave.
All three answers must be correct in one attempt. A failed attempt can be
retried from the menu. This is a query-reading assessment, not proof of tool use.
)";

        const std::vector<Exercise> questions =
        {
            {
                "SELECT name FROM inventory WHERE category = 'Tools' AND published = 1 AND price <= 40;",
                "How many rows are returned?",
                "2",
                "",
                ""
            },
            {
                "SELECT name FROM inventory WHERE category = 'Tools' OR category = 'Books' AND published = 1;",
                "How many rows are returned?",
                "4",
                "",
                ""
            },
            {
                "SELECT name, price FROM inventory WHERE published = 1 AND price < 40;",
                "What is the sum of the returned prices?",
                "35",
                "",
                ""
            }
        };

        bool passed = true;

        for (const Exercise& question : questions)
        {
            output << '\n' << question.query << '\n'
                << question.prompt << "\nAnswer: ";

            const std::string answer = Read(input);

            if (answer == "back")
            {
                passed = false;
                break;
            }

            if (answer != question.answer)
            {
                output << "Attempt not passed. Review WHERE, AND/OR grouping, "
                    << "and strict versus inclusive comparisons.\n";

                passed = false;
                break;
            }
        }

        if (passed)
        {
            output << "\nSQL FUNDAMENTALS ASSESSMENT PASSED (3/3).\n"
                << "Save from the main menu to keep this progress.\n"
                << "No external lab completion is recorded. Any eligible XP is awarded when returning to the main menu..\n";
        }

        return passed;
    }

    static void DockerGuide(std::ostream& output)
    {
        output << R"(
REAL DATABASE PRACTICE - Windows PowerShell and browser
From the repository root in PowerShell:
docker compose -f ./labs/compose.yaml up -d --build
curl.exe --noproxy "*" http://127.0.0.1:8085/health

Open http://127.0.0.1:8085 in your browser.
1. In Vulnerable query mode, search Training Notebook. Read SELECT/FROM/WHERE
   in Query details. Identify the selected columns and the two conditions.
2. Search BBT Hidden Training Record by its exact name. Why is it excluded?
3. Compare the query template displayed in Parameterized query mode.
   Identify the placeholder and the separately bound value.
4. Write down expected results and actual results in your own notes.

This guide does not launch Docker or inspect your browser. The assessment
cannot certify these actions. External objective verification is future work.
Stop the lab in PowerShell with:
docker compose -f ./labs/compose.yaml stop
)";
    }

public:
    bool IsRewardClaimed() const
    {
        return rewardClaimed;
    }

    void MarkRewardClaimed()
    {
        if (assessmentComplete)
        {
            rewardClaimed = true;
        }
    }
    bool IsGuidedComplete() const
    {
        return guidedComplete;
    }

    bool IsAssessmentComplete() const
    {
        return assessmentComplete;
    }

    // Restore saved flags without awarding XP.
    void RestoreProgress(
        bool guided,
        bool assessment,
        bool claimed = false)
    {
        guidedComplete = guided;
        assessmentComplete = guided && assessment;
        rewardClaimed = assessmentComplete && claimed;
    }

    void Run(
        std::istream& input = std::cin,
        std::ostream& output = std::cout)
    {
        bool open = true;

        while (open)
        {
            output << "\n========== SQL FUNDAMENTALS ==========\n";
            output << "Stage 1 of the planned SQL injection course\n";
            output << "Guided practice: "
                << (guidedComplete ? "Complete" : "Not complete") << '\n';
            output << "Assessment: "
                << (assessmentComplete ? "Passed" : "Not passed") << '\n';
            output << "SQL progress is included when you save from the main menu.\n";
            output << "Assessment reward: 150 XP, awarded once when returning to the main menu.\n";
            output << "1. Read lesson\n";
            output << "2. Guided query practice\n";
            output << "3. Independent assessment\n";
            output << "4. Docker practice guide\n";
            output << "0. Return to main menu\n";
            output << "Choice: ";

            const std::string choice = Read(input);

            if (choice == "0")
            {
                open = false;
            }
            else if (choice == "1")
            {
                Lesson(output);
            }
            else if (choice == "2")
            {
                guidedComplete = Guided(input, output) || guidedComplete;
            }
            else if (choice == "3")
            {
                if (!guidedComplete)
                {
                    output << "Complete guided practice before "
                        << "the independent assessment.\n";
                }
                else if (assessmentComplete)
                {
                    output << "Assessment already passed.\n ";
                }
                else
                {
                    assessmentComplete = Assess(input, output);
                }
            }
            else if (choice == "4")
            {
                DockerGuide(output);
            }
            else
            {
                output << "Invalid selection. Enter 0, 1, 2, 3, or 4.\n";
            }
        }
    }
};