#include "../include/LearningPathManager.h"

#include <array>
#include <iostream>
#include <string>
#include <vector>

// Lesson content and assessment execution belong to the learning-path system.
namespace
{
    struct LessonQuestion
    {
        std::string prompt;
        std::array<std::string, 3> options;
        int correctIndex;
    };

    struct ModuleLesson
    {
        int moduleIndex;
        std::string title;
        std::string lesson;
        std::string scenario;
        std::vector<LessonQuestion> questions;
    };

    const ModuleLesson* FindModuleLesson(int moduleIndex)
    {
        // Every assessment uses the same runner; content belongs in this table.
        static const std::vector<ModuleLesson> lessons =
        {
            {
                3,
                "Networking Fundamentals",
                R"(A hostname is a readable name; an IP address identifies a network endpoint.
DNS can resolve a hostname to an IP address.
A port identifies a service endpoint on a host. An IP address and port are
different pieces of information.
TCP provides a reliable, ordered byte stream. UDP carries datagrams without
guaranteeing delivery or order.
Common defaults: HTTPS uses TCP port 443; SSH uses TCP port 22; DNS commonly
uses port 53 over UDP or TCP. A port number alone does not prove service identity.
Before interacting with a service, confirm both the target and activity are
authorized. An observed service is not automatically an authorized target.
)",
                R"(SIMULATED SERVICE REPORT
Hostname: portal.training.test
Address: 192.0.2.10
Services: 22/tcp SSH, 443/tcp HTTPS, 53/udp DNS
Lab scope: portal.training.test, HTTPS on port 443 only.

Activity: identify the hostname, address, permitted service, and transport.
Use this report to answer the questions. No network requests are made.
)",
                {
                    {"Which service translates a hostname to an IP address?",
                        {"SSH", "DNS", "HTTPS"}, 1},
                    {"Which service is explicitly permitted by this lab's scope?",
                        {"SSH on port 22", "All discovered services", "HTTPS on port 443"}, 2},
                    {"Which transport provides a reliable, ordered byte stream?",
                        {"TCP", "UDP", "DNS"}, 0},
                    {"What does port 443 identify in this report?",
                        {"The researcher's identity", "The host's physical location", "The HTTPS service endpoint"}, 2},
                    {"What should you assume about delivery of a UDP datagram?",
                        {"Delivery and ordering are not guaranteed", "It always arrives before TCP", "It is encrypted automatically"}, 0}
                }
            },
            {
                4,
                "Web Fundamentals",
                R"(HTTP follows a request/response model. A request includes a method, a path,
headers, and sometimes a body. The response includes a status code and content.
GET requests retrieve a representation; POST requests submit data for processing.
Cookies let browsers send stored values back to a server. A session cookie may
identify a signed-in session and should be treated as sensitive.
A 200 response indicates success. A 401 response means valid authentication
credentials are missing or unacceptable. A 403 response means access is refused.
HTTPS protects data in transit; the server must still check permissions.
Changing an identifier in a URL must never replace server-side authorization.
)",
                R"(SIMULATED WEB EXCHANGE
Request:
GET /account HTTP/1.1
Host: portal.training.test
Cookie: session=demo-session-value

Response:
HTTP/1.1 200 OK
Content-Type: text/html

The demonstration session value is fictional.
Activity: identify the method, path, state-carrying header, and response meaning.
)",
                {
                    {"Which HTTP method appears in the request?",
                        {"POST", "GET", "DELETE"}, 1},
                    {"Which path is being requested?",
                        {"/account", "portal.training.test", "text/html"}, 0},
                    {"Which header carries the demonstration session value?",
                        {"Content-Type", "Host", "Cookie"}, 2},
                    {"What does HTTP 401 indicate?",
                        {"The page moved permanently", "Valid authentication credentials are required", "The request definitely succeeded"}, 1},
                    {"Does HTTPS remove the need for server-side permission checks?",
                        {"Yes, encryption proves ownership", "Yes, cookies grant access to every account", "No, authorization must still be enforced"}, 2}
                }
            },
            {
                5,
                "Reconnaissance",
                R"(Reconnaissance collects and organizes information before validation.
Passive research uses existing information, such as published documentation.
Active reconnaissance interacts with a target and requires permission for that
target and activity. Public visibility does not itself grant testing permission.
Record the source, observation, and time. Separate confirmed facts from guesses.
An asset inventory can include hostnames, services, owners, and scope status.
A third-party host linked from an authorized site is not automatically in scope.
Work from explicit scope, and request clarification when ownership is uncertain.
)",
                R"(SIMULATED ASSET INVENTORY
portal.training.test | HTTPS | Listed in scope
api.training.test    | HTTPS | Listed in scope
cdn.vendor.test      | HTTPS | Third-party service, not listed in scope

Evidence: API documentation lists /v1/profile as an endpoint.
No request to /v1/profile has been made.

Activity: distinguish permitted assets, documented observations, and assumptions.
)",
                {
                    {"Which asset should be excluded unless separately authorized?",
                        {"api.training.test", "cdn.vendor.test", "portal.training.test"}, 1},
                    {"Which example is passive research?",
                        {"Reading already-published API documentation", "Sending test payloads", "Running a service scan"}, 0},
                    {"What can you conclude from the documented /v1/profile endpoint?",
                        {"It is vulnerable", "It exposes every user's profile", "It is documented; its behavior is not yet verified"}, 2},
                    {"What makes a reconnaissance note useful?",
                        {"A guess with no source", "A source, observation, and recorded time", "Only the number of URLs collected"}, 1},
                    {"Before actively testing a newly discovered hostname, what comes first?",
                        {"Confirm explicit scope and permitted activities", "Assume related names are authorized", "Test it before writing it down"}, 0}
                }
            },
            {
                6,
                "Web Vulnerability Fundamentals",
                R"(Authentication establishes who a user is. Authorization determines what that
user may access. Both must be enforced on the server.
An insecure direct object reference can occur when a server accepts a record
identifier without checking whether the requesting user may access that record.
For SQL queries, parameterized statements separate values from query structure.
Input validation is useful, but does not replace parameterized queries.
Cross-site scripting prevention includes context-appropriate output encoding;
treat untrusted text as data rather than executable browser content.
Validate suspected issues using authorized test accounts and minimal evidence.
A suspicious response alone is not proof of a vulnerability.
)",
                R"(SIMULATED OWNERSHIP CHECK
Test account A owns record 101.
Test account B owns record 202.
Both accounts are provided by this training lab.

The server receives an authenticated request for a record identifier.
Activity: choose the expected permission check and appropriate prevention.
These questions describe a simulation; do not access real users' records.
)",
                {
                    {"Before returning record 202 to account A, what must the server check?",
                        {"Only that A is signed in", "That the URL contains a number", "That A is authorized to access record 202"}, 2},
                    {"What is the main purpose of authentication?",
                        {"Establish the user's identity", "Grant access to every record", "Remove the need for authorization"}, 0},
                    {"Which approach separates SQL values from query structure?",
                        {"Concatenating user input", "Parameterized statements", "Hiding the database error message"}, 1},
                    {"Which helps prevent untrusted text becoming executable browser content?",
                        {"A longer page title", "Context-appropriate output encoding", "Only changing the URL"}, 1},
                    {"How should an ownership-check finding be validated in this lab?",
                        {"Use unrelated real accounts", "Download as much data as possible", "Use the provided accounts and minimal evidence"}, 2}
                }
            },
            {
                7,
                "Bug Bounty Methodology",
                R"(A repeatable workflow starts with scope and rules, then reconnaissance,
a testable hypothesis, minimal authorized validation, and reporting.
Keep notes of actions and observations so someone else can reproduce the result.
Separate expected behavior, actual behavior, and supported security impact.
A useful report includes the affected component, prerequisites, numbered steps,
expected and actual results, minimal evidence, impact, and a suggested remedy.
Redact session tokens, passwords, and unrelated personal data from evidence.
Avoid duplicate or unverified reports; a tool alert is a lead, not a confirmed bug.
When a test risks exceeding scope or causing harm, stop and seek clarification.
)",
                R"(SIMULATED REPORT DRAFT
Title: Account A can read account B's lab record
Prerequisite: Two instructor-provided test accounts
Observation: An authorized lab test returned B's record to A
Missing details: exact steps, expected behavior, minimal evidence, and impact

Activity: improve reproducibility and support the report's claims.
Keep all reproduction steps limited to the fictional training environment.
)",
                {
                    {"What should happen before reconnaissance and validation?",
                        {"Confirm scope and program rules", "Publish a report", "Choose a reward amount"}, 0},
                    {"Which addition most improves reproducibility?",
                        {"More dramatic wording", "Prerequisites and numbered steps with expected and actual results", "A claim that every account is affected"}, 1},
                    {"How should session tokens appear in shared report evidence?",
                        {"Always publish their full values", "Use them as the report title", "Redact them unless a secure agreed process requires them"}, 2},
                    {"What does an automated scanner alert establish by itself?",
                        {"A confirmed high-impact vulnerability", "A lead requiring authorized validation", "Permission to test related systems"}, 1},
                    {"Which impact statement is strongest?",
                        {"Every system is compromised", "The reward should be large", "The provided account could read another test account's record"}, 2}
                }
            }
        };

        for (const ModuleLesson& lesson : lessons)
        {
            if (lesson.moduleIndex == moduleIndex)
            {
                return &lesson;
            }
        }
        return nullptr;
    }

    bool RunModuleLesson(
        const ModuleLesson& lesson,
        const LearningPathManager::AnswerShuffler& shuffleAnswerPositions,
        const LearningPathManager::LetterAnswerReader& readLetterAnswer)
    {
        std::cout << "\n====================================\n";
        std::cout << lesson.title << '\n';
        std::cout << "====================================\n\n";
        std::cout << lesson.lesson << "\n" << lesson.scenario;
        std::cout << "\nKNOWLEDGE ASSESSMENT\n";
        std::cout << "Answer all " << lesson.questions.size()
            << " questions correctly to complete this module.\n";

        int correctAnswers = 0;
        for (int i = 0; i < static_cast<int>(lesson.questions.size()); ++i)
        {
            const LessonQuestion& question = lesson.questions[i];
            const std::vector<int> order = shuffleAnswerPositions(
                lesson.title + " Q" + std::to_string(i),
                static_cast<int>(question.options.size()),
                question.correctIndex);

            std::cout << "\n" << i + 1 << ". " << question.prompt << "\n\n";
            for (int option = 0; option < static_cast<int>(order.size()); ++option)
            {
                std::cout << "   " << static_cast<char>('a' + option) << ". "
                    << question.options[order[option]] << '\n';
            }
            std::cout << '\n';

            const int selectedPosition =
                readLetterAnswer(static_cast<int>(order.size()));
            if (order[selectedPosition] == question.correctIndex)
            {
                ++correctAnswers;
            }
        }

        std::cout << "\nAssessment Score: " << correctAnswers
            << "/" << lesson.questions.size() << '\n';
        const bool passed =
            correctAnswers == static_cast<int>(lesson.questions.size());
        if (!passed)
        {
            std::cout << "Assessment not passed. No XP awarded.\n";
            std::cout << "Review the lesson and reopen this module to try again.\n";
        }
        return passed;
    }

}

void LearningPathManager::Display(
    const Researcher& researcher,
    const std::vector<LearningModule>& learningModules)
{
    std::cout << "\n====================================\n";
    std::cout << "           LEARNING PATH\n";
    std::cout << "====================================\n";

    std::cout << "Researcher Level: "
        << researcher.GetLevel() << std::endl;

    std::cout << "Total XP: "
        << researcher.GetTotalXP() << std::endl;

    std::cout << "Available XP: "
        << researcher.GetAvailableXP() << std::endl;

    std::cout << "====================================\n\n";

    for (int i = 0;
        i < static_cast<int>(learningModules.size());
        i++)
    {
        std::cout << i + 1 << ". ";

        if (learningModules[i].IsCompleted())
        {
            std::cout << "[COMPLETED] ";
        }
        else if (learningModules[i].IsUnlocked())
        {
            std::cout << "[AVAILABLE] ";
        }
        else
        {
            std::cout << "[LOCKED] ";
        }

        std::cout << "Level "
            << learningModules[i].GetModuleLevel()
            << " - "
            << learningModules[i].GetTitle()
            << std::endl;

        std::cout << "   Difficulty: "
            << learningModules[i].GetDifficulty()
            << std::endl;

        std::cout << "   XP Reward: "
            << learningModules[i].GetXPReward()
            << " XP\n";

        std::cout << "   Unlock Cost: "
            << learningModules[i].GetUnlockCost()
            << " XP\n";

        std::cout << "   Required Level: "
            << learningModules[i].GetRequiredLevel()
            << std::endl;

        std::cout << std::endl;
    }

    std::cout << "0. Return to Main Menu\n";
    std::cout << "====================================\n";
}

// ====================================
// Open Learning Path
// ====================================

void LearningPathManager::Run(
    Researcher& researcher,
    std::vector<LearningModule>& learningModules,
    const std::vector<Challenge>& challenges,
    const std::vector<Lab>& labs,
    const ChoiceReader& getValidatedChoice,
    const PauseAction& pause,
    const AnswerShuffler& shuffleAnswerPositions,
    const LetterAnswerReader& readLetterAnswer)
{
    bool viewingLearningPath = true;

    while (viewingLearningPath)
    {
        Display(researcher, learningModules);

        std::cout << "Select a module: ";

        int choice = getValidatedChoice(
            0,
            static_cast<int>(learningModules.size()));

        if (choice == 0)
        {
            viewingLearningPath = false;
            continue;
        }

        int moduleIndex = choice - 1;

        LearningModule* selectedModule =
            &learningModules[moduleIndex];

        // ====================================
        // Locked Module
        // ====================================

        if (!selectedModule->IsUnlocked())
        {
            std::cout << "\n====================================\n";
            std::cout << "           MODULE LOCKED\n";
            std::cout << "====================================\n";

            std::cout << "Module: "
                << selectedModule->GetTitle()
                << std::endl;

            std::cout << "Required Level: "
                << selectedModule->GetRequiredLevel()
                << std::endl;

            std::cout << "Unlock Cost: "
                << selectedModule->GetUnlockCost()
                << " XP\n";

            std::cout << "Available XP: "
                << researcher.GetAvailableXP()
                << std::endl;

            // Check whether the previous module
            // has been completed.
            if (moduleIndex > 0)
            {
                LearningModule* previousModule =
                    &learningModules[moduleIndex - 1];

                if (!previousModule->IsCompleted())
                {
                    std::cout << "\n====================================\n";
                    std::cout << "      PREREQUISITE NOT MET\n";
                    std::cout << "====================================\n";

                    std::cout << "You must complete:\n";

                    std::cout << "Level "
                        << previousModule->GetModuleLevel()
                        << " - "
                        << previousModule->GetTitle()
                        << std::endl;

                    pause();
                    continue;
                }
            }

            // Check researcher level.
            if (researcher.GetLevel() <
                selectedModule->GetRequiredLevel())
            {
                std::cout << "\nYour researcher level is too low.\n";

                std::cout << "Required Level: "
                    << selectedModule->GetRequiredLevel()
                    << std::endl;

                pause();
                continue;
            }

            // Check available XP.
            if (researcher.GetAvailableXP() <
                selectedModule->GetUnlockCost())
            {
                std::cout << "\nNot enough available XP.\n";

                pause();
                continue;
            }

            // Allow the researcher to purchase the module.
            std::cout << "\nPrerequisites completed.\n\n";
            std::cout << "1. Purchase Module\n";
            std::cout << "2. Cancel\n";
            std::cout << "Choice: ";

            int purchaseChoice = getValidatedChoice(1, 2);

            if (purchaseChoice == 2)
            {
                continue;
            }

            if (researcher.SpendXP(
                selectedModule->GetUnlockCost()))
            {
                selectedModule->UnlockModule();
                // ====================================
// Check for Previously Completed Lab
// ====================================

// Computer Fundamentals requires the
// Terminal Investigation hands-on lab.
//
// If the lab was completed before the
// module was unlocked, complete the
// module now.
                if (moduleIndex == 1 &&
                    labs[0].IsCompleted() &&
                    !selectedModule->IsCompleted())
                {
                    selectedModule->CompleteModule();

                    if (selectedModule->IsCompleted())
                    {
                        researcher.AddXP(
                            selectedModule->GetXPReward());

                        std::cout << "\n====================================\n";
                        std::cout << "       LEARNING MODULE COMPLETE!\n";
                        std::cout << "====================================\n";

                        std::cout
                            << selectedModule->GetTitle()
                            << " completed successfully!\n";

                        std::cout << "\nModule XP Bonus: "
                            << selectedModule->GetXPReward()
                            << " XP\n";

                        std::cout
                            << "\nYour previously completed "
                            << "Terminal Investigation lab "
                            << "satisfied the module requirement.\n";

                        std::cout << "====================================\n";
                    }
                }

                std::cout << "\n====================================\n";
                std::cout << "          MODULE UNLOCKED!\n";
                std::cout << "====================================\n";

                std::cout << selectedModule->GetTitle()
                    << " is now available.\n";

                std::cout << "Available XP: "
                    << researcher.GetAvailableXP()
                    << std::endl;

                pause();
            }

            continue;
        }

        // ====================================
        // Already Completed Module
        // ====================================

        if (selectedModule->IsCompleted())
        {
            selectedModule->DisplayModule();

            std::cout
                << "\nThis module has already been completed.\n";

            pause();
            continue;
        }

        // ====================================
        // Module Training
        // ====================================

        selectedModule->DisplayModule();

        std::cout << "\n====================================\n";
        std::cout << "           MODULE TRAINING\n";
        std::cout << "====================================\n";

        // Level 0 requires two challenges.
        if (moduleIndex == 0)
        {
            std::cout
                << "Complete both challenges from Start Training:\n\n";

            std::cout << "1. Authorization Basics: ";

            if (challenges[0].IsCompleted())
            {
                std::cout << "Completed\n";
            }
            else
            {
                std::cout << "Not Completed\n";
            }

            std::cout << "2. Scope Basics: ";

            if (challenges[1].IsCompleted())
            {
                std::cout << "Completed\n";
            }
            else
            {
                std::cout << "Not Completed\n";
            }

            std::cout
                << "\nCompleting both challenges will automatically "
                << "complete this learning module.\n";

            std::cout
                << "You will also earn the module XP bonus.\n";
        }
        else if (moduleIndex == 1)
        {
            std::cout
                << "Required Hands-On Lab:\n\n";

            std::cout << "1. Terminal Investigation: ";

            if (labs[0].IsCompleted())
            {
                std::cout << "Completed\n";
            }
            else
            {
                std::cout << "Not Completed\n";
            }

            std::cout
                << "\nComplete Terminal Investigation from "
                << "Hands-On Labs to automatically complete "
                << "Computer Fundamentals.\n";

            std::cout
                << "You will also earn the module XP bonus.\n";
        }
        else if (moduleIndex == 2)
        {
            // Linux Fundamentals: shuffled answer letters on every attempt.
            struct LinuxQuestion
            {
                std::string prompt;
                std::array<std::string, 3> options;
                int correctIndex;
            };
            const std::array<LinuxQuestion, 3> questions = { {
                {"Which command lists files?", {"pwd", "ls", "cd"}, 1},
                {"Which command displays your current directory?", {"pwd", "cat", "mkdir"}, 0},
                {"Which command changes file permissions?", {"ls", "cd", "chmod"}, 2}
            } };

            std::cout << "\nLINUX FUNDAMENTALS\n\n"
                << "pwd   - Display the current directory.\n"
                << "ls    - List files and directories.\n"
                << "cd    - Change directories.\n"
                << "cat   - Display file contents.\n"
                << "mkdir - Create a directory.\n"
                << "chmod - Change file permissions.\n"
                << "\nKNOWLEDGE ASSESSMENT\n"
                << "Answer all three questions correctly to pass.\n";

            int correctAnswers = 0;
            for (int i = 0; i < static_cast<int>(questions.size()); ++i)
            {
                const auto& question = questions[i];
                std::vector<int> order = shuffleAnswerPositions(
                    "Linux Fundamentals Q" + std::to_string(i),
                    3, question.correctIndex);
                std::cout << "\n" << i + 1 << ". " << question.prompt << "\n\n";
                for (int j = 0; j < 3; ++j)
                {
                    std::cout << "   " << static_cast<char>('a' + j)
                        << ". " << question.options[order[j]] << "\n";
                }
                std::cout << "\n";
                int selectedPosition = readLetterAnswer(3);
                if (order[selectedPosition] == question.correctIndex)
                {
                    ++correctAnswers;
                }
            }

            std::cout << "\nAssessment Score: " << correctAnswers << "/3\n";
            if (correctAnswers == 3 && !selectedModule->IsCompleted())
            {
                selectedModule->CompleteModule();
                if (selectedModule->IsCompleted())
                {
                    researcher.AddXP(selectedModule->GetXPReward());
                    std::cout << "\n[MODULE COMPLETE] Linux Fundamentals!\n"
                        << "XP Earned: " << selectedModule->GetXPReward()
                        << "\nNetworking Fundamentals can now be unlocked "
                        << "when its requirements are met.\n";
                }
            }
            else if (correctAnswers != 3)
            {
                std::cout << "Assessment not passed. Review the lesson and try again.\n";
            }
        }
        else
        {
            const ModuleLesson* lesson = FindModuleLesson(moduleIndex);
            if (lesson == nullptr)
            {
                std::cout << "No training activity is assigned to this module.\n";
            }
            else if (RunModuleLesson(*lesson, shuffleAnswerPositions, readLetterAnswer) && !selectedModule->IsCompleted())
            {
                selectedModule->CompleteModule();
                if (selectedModule->IsCompleted())
                {
                    researcher.AddXP(selectedModule->GetXPReward());
                    std::cout << "\n[MODULE COMPLETE] "
                        << selectedModule->GetTitle() << "!\n";
                    std::cout << "XP Earned: " << selectedModule->GetXPReward() << '\n';

                    if (moduleIndex + 1 < static_cast<int>(learningModules.size()))
                    {
                        std::cout << learningModules[moduleIndex + 1].GetTitle()
                            << " can now be unlocked when its requirements are met.\n";
                    }
                    else
                    {
                        std::cout << "You completed the current learning path!\n";
                    }
                }
            }
        }
        pause();
    }
}
// ====================================
// Display Hands-On Labs
// ====================================
