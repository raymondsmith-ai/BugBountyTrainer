#include "../include/TrainerApp.h"
#include "../include/SaveManager.h"

#include <iostream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <array>
#include <random>
#include <unordered_map>
#include <numeric>
#include <cctype>
#include <filesystem>
#include <fstream>
#include "../include/DockerLabClient.h"





// Shared assessment helpers. The last correct-answer position is remembered
// for each question during this application session, including retakes.
namespace
{
    bool HasSupportedSaveFormat(const std::filesystem::path& path)
    {
        std::ifstream file(path);
        std::string version;

        return std::getline(file, version) &&
            (version == "BBT_SAVE_V2" ||
                version == "BBT_SAVE_V3" ||
                version == "BBT_SAVE_V4" ||
                version == "BBT_SAVE_V5" ||
                version == "BBT_SAVE_V6");
    }

    std::vector<std::filesystem::path> FindSaveFiles(bool supportedOnly)
    {
        const std::string prefix = "researcher_save_";
        const std::string suffix = ".txt";
        std::vector<std::filesystem::path> saveFiles;
        std::error_code error;
        std::filesystem::directory_iterator entry(".", error);
        const std::filesystem::directory_iterator end;

        while (!error && entry != end)
        {
            const std::filesystem::path path = entry->path();
            if (entry->is_regular_file(error) && !entry->is_symlink(error))
            {
                const std::string filename = path.filename().string();
                const bool isLegacySave = filename == "researcher_save.txt";
                const bool isUserSave =
                    filename.rfind(prefix, 0) == 0 &&
                    filename.size() > prefix.size() + suffix.size() &&
                    filename.compare(filename.size() - suffix.size(),
                        suffix.size(), suffix) == 0;

                if ((isLegacySave || isUserSave) &&
                    (!supportedOnly || HasSupportedSaveFormat(path)))
                {
                    saveFiles.push_back(path);
                }
            }
            if (!error)
            {
                entry.increment(error);
            }
        }

        if (error)
        {
            throw std::runtime_error("Unable to read the saved-user folder.");
        }

        std::sort(saveFiles.begin(), saveFiles.end());
        return saveFiles;
    }

   
        std::string SavedUserLabel(const std::filesystem::path & path)
        {
            std::ifstream file(path);
            std::string version;
            std::string name;
            if (std::getline(file, version) &&
                (version == "BBT_SAVE_V2" ||
                    version == "BBT_SAVE_V3" ||
                    version == "BBT_SAVE_V4" ||
                    version == "BBT_SAVE_V5" ||
                    version == "BBT_SAVE_V6") &&
                std::getline(file, name) &&
                !name.empty())
            {
                return name;
            }

            return path.filename().string() + " [unsupported or unreadable]";
        }

    std::string GenerateValidationCode()
    {
        static constexpr char characters[] =
            "ABCDEFGHJKLMNPQRSTUVWXYZ23456789";
        static std::mt19937 generator(std::random_device{}());
        std::uniform_int_distribution<int> distribution(
            0, static_cast<int>(sizeof(characters) - 2));

        std::string code = "BBT-";
        for (int i = 0; i < 8; ++i)
        {
            if (i == 4)
            {
                code += '-';
            }
            code += characters[distribution(generator)];
        }
        return code;
    }

    std::string SaveFilenameFor(const std::string& name)
    {
        std::string safeName;
        for (unsigned char ch : name)
        {
            if (std::isalnum(ch) || ch == '-' || ch == '_')
            {
                safeName += static_cast<char>(ch);
            }
            else if (safeName.empty() || safeName.back() != '_')
            {
                safeName += '_';
            }
        }

        while (!safeName.empty() && safeName.back() == '_')
        {
            safeName.pop_back();
        }
        if (safeName.empty())
        {
            safeName = "Researcher";
        }
        return "researcher_save_" + safeName + ".txt";
    }

    std::mt19937& AssessmentRng()
    {
        static std::mt19937 rng(std::random_device{}());
        return rng;
    }

    // Returns shuffled original answer indices, with the correct answer
    // moved to a different letter than on the previous attempt.
    std::vector<int> ShuffleAnswerPositions(
        const std::string& questionKey, int count, int correctIndex)
    {
        static std::unordered_map<std::string, int> lastCorrectPosition;
        std::vector<int> order(count);
        std::iota(order.begin(), order.end(), 0);
        std::shuffle(order.begin(), order.end(), AssessmentRng());

        auto previous = lastCorrectPosition.find(questionKey);
        if (previous != lastCorrectPosition.end() && count > 1)
        {
            auto it = std::find(order.begin(), order.end(), correctIndex);
            int current = static_cast<int>(it - order.begin());
            if (current == previous->second)
            {
                int swapPosition = (current + 1) % count;
                std::swap(order[current], order[swapPosition]);
            }
        }

        auto it = std::find(order.begin(), order.end(), correctIndex);
        lastCorrectPosition[questionKey] = static_cast<int>(it - order.begin());
        return order;
    }

    // Read a single a/b/c answer, accepting uppercase as well.
    int ReadLetterAnswer(int count)
    {
        while (true)
        {
            std::cout << "Enter your answer (a, b, or c): ";
            std::string input;
            if (!std::getline(std::cin, input))
            {
                throw std::runtime_error("Input stream closed.");
            }
            if (input.size() == 1)
            {
                char letter = input[0];
                if (letter >= 'A' && letter <= 'Z')
                {
                    letter = static_cast<char>(letter - 'A' + 'a');
                }
                int index = letter - 'a';
                if (index >= 0 && index < count)
                {
                    return index;
                }
            }
            std::cout << "Invalid answer. Please enter a valid letter.\n";
        }
    }

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

    bool RunModuleLesson(const ModuleLesson& lesson)
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
            const std::vector<int> order = ShuffleAnswerPositions(
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
                ReadLetterAnswer(static_cast<int>(order.size()));
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

// ====================================
// Constructor
// ====================================

TrainerApp::TrainerApp(const std::string& researcherName)
    : researcher(researcherName), running(true)
{
    // ====================================
    // Training Challenges
    // ====================================

    challenges.push_back(
        Challenge(
            "Authorization Basics",
            "Learn why permission is required before security testing.",
            "Authorization",
            "Easy",
            100,
            "Before testing a website for vulnerabilities, what should you verify first?",
            {
                "The website has a login page",
                "You have authorization to test the target",
                "The website uses HTTPS"
            },
            2
        )
    );

    challenges.push_back(
        Challenge(
            "Scope Basics",
            "Learn why bug bounty scope must be followed.",
            "Rules & Ethics",
            "Easy",
            150,
            "What should you do if a website or domain is not listed as an authorized target?",
            {
                "Test it anyway",
                "Do not test it unless you receive authorization",
                "Test only the login page"
            },
            2
        )
    );

    challenges.push_back(
        Challenge(
            "Input Validation Basics",
            "Learn why applications should validate user input.",
            "Input Validation",
            "Medium",
            200,
            "Why is input validation important?",
            {
                "It helps prevent unexpected or invalid data from being processed",
                "It makes every password stronger",
                "It removes the need for testing"
            },
            1
        )
    );

    // ====================================
    // Learning Modules
    // ====================================

    learningModules.push_back(
        LearningModule(
            "Rules, Ethics & Authorization",
            "Learn the legal and ethical rules of security testing.",
            "Beginner",
            0,
            1,
            100,
            0,
            true
        )
    );

    learningModules.push_back(
        LearningModule(
            "Computer Fundamentals",
            "Learn how computers, files, processes, users, and operating systems work.",
            "Beginner",
            1,
            1,
            125,
            50,
            false
        )
    );

    learningModules.push_back(
        LearningModule(
            "Linux Fundamentals",
            "Learn terminal navigation, commands, files, and permissions.",
            "Beginner",
            2,
            1,
            150,
            100,
            false
        )
    );

    learningModules.push_back(
        LearningModule(
            "Networking Fundamentals",
            "Learn IP addresses, ports, protocols, DNS, TCP, and UDP.",
            "Beginner",
            3,
            2,
            200,
            150,
            false
        )
    );

    learningModules.push_back(
        LearningModule(
            "Web Fundamentals",
            "Learn HTTP, requests, responses, headers, cookies, and web applications.",
            "Beginner",
            4,
            2,
            250,
            200,
            false
        )
    );

    learningModules.push_back(
        LearningModule(
            "Reconnaissance",
            "Learn how authorized researchers discover and organize information about a target.",
            "Intermediate",
            5,
            3,
            300,
            300,
            false
        )
    );

    learningModules.push_back(
        LearningModule(
            "Web Vulnerability Fundamentals",
            "Learn common web weaknesses inside authorized training environments.",
            "Intermediate",
            6,
            4,
            400,
            400,
            false
        )
    );

    learningModules.push_back(
        LearningModule(
            "Bug Bounty Methodology",
            "Learn how to organize research, validate findings, collect evidence, and prepare reports.",
            "Advanced",
            7,
            5,
            500,
            500,
            false
        )
    );

    // ====================================
    // Hands-On Labs
    // ====================================

    Lab terminalLab(
        "Terminal Investigation",
        "Practice investigating a simulated BugBountyTrainer workstation using terminal commands.",
        "Beginner",
        150,
        true
    );

    terminalLab.AddObjective("Identify the current user.");
    terminalLab.AddObjective("List the files in the training directory.");
    terminalLab.AddObjective("Read the training.txt file.");
    terminalLab.AddObjective("Recover the validation code.");

    labs.push_back(terminalLab);

    // Future training lab.
    Lab networkLab(
        "Network Discovery",
        "Practice identifying services inside an isolated training network.",
        "Beginner",
        200,
        false
    );

    networkLab.AddObjective("Identify the training target.");
    networkLab.AddObjective("Discover the exposed service.");
    networkLab.AddObjective("Identify the service type.");

    labs.push_back(networkLab);
}

// ====================================
// Main Menu
// ====================================

void TrainerApp::DisplayMenu() const
{
    std::cout << "\n====================================\n";
    std::cout << "        BUG BOUNTY TRAINER\n";
    std::cout << "====================================\n";

    std::cout << "Researcher: "
        << researcher.GetName() << std::endl;

    std::cout << "Level: "
        << researcher.GetLevel() << std::endl;

    std::cout << "Total XP: "
        << researcher.GetTotalXP() << std::endl;

    std::cout << "Available XP: "
        << researcher.GetAvailableXP() << std::endl;

    std::cout << "====================================\n";
    std::cout << "1. View Researcher Profile\n";
    std::cout << "2. Learning Path\n";
    std::cout << "3. Hands-On Labs\n";
    std::cout << "4. Start Training\n";
    std::cout << "5. View Challenges\n";
    std::cout << "6. Browse Vulnerability Categories\n";
    std::cout << "7. Save Progress\n";
    std::cout << "8. Load Progress\n";
    std::cout << "9. Exit\n";
    std::cout << "10. SQL Fundamentals (Stage 1)\n";
    std::cout << "11. SQL Injection Training (Stage 2)\n";
    std::cout << "12. Docker SQL Injection Labs\n";
    std::cout << "13. SQL Academy (13 Modules)\n";

    std::cout << "====================================\n";
    std::cout << "Enter a number from 1 to 13: ";
}

// ====================================
// Validate Menu Input
// ====================================

int TrainerApp::GetValidatedChoice(int minimum, int maximum) const
{
    std::string input;

    while (true)
    {
        if (!std::getline(std::cin, input))
        {
            throw std::runtime_error("Input stream closed.");
        }

        try
        {
            std::size_t position = 0;
            int choice = std::stoi(input, &position);

            // Reject extra characters, such as 2abc.
            if (position != input.length())
            {
                throw std::invalid_argument("Extra characters");
            }

            if (choice >= minimum && choice <= maximum)
            {
                return choice;
            }

            std::cout << "\nInvalid selection. Choose a number from "
                << minimum << " to " << maximum << ".\n";
        }
        catch (const std::invalid_argument&)
        {
            std::cout << "\nInvalid input. Please enter a whole number.\n";
        }
        catch (const std::out_of_range&)
        {
            std::cout << "\nNumber is too large. Please try again.\n";
        }

        std::cout << "Enter your choice: ";
    }
}

// ====================================
// Display Learning Path
// ====================================

void TrainerApp::DisplayLearningPath() const
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

void TrainerApp::OpenLearningPath()
{
    bool viewingLearningPath = true;

    while (viewingLearningPath)
    {
        DisplayLearningPath();

        std::cout << "Select a module: ";

        int choice = GetValidatedChoice(
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

                    Pause();
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

                Pause();
                continue;
            }

            // Check available XP.
            if (researcher.GetAvailableXP() <
                selectedModule->GetUnlockCost())
            {
                std::cout << "\nNot enough available XP.\n";

                Pause();
                continue;
            }

            // Allow the researcher to purchase the module.
            std::cout << "\nPrerequisites completed.\n\n";
            std::cout << "1. Purchase Module\n";
            std::cout << "2. Cancel\n";
            std::cout << "Choice: ";

            int purchaseChoice = GetValidatedChoice(1, 2);

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

                Pause();
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

            Pause();
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
                std::vector<int> order = ShuffleAnswerPositions(
                    "Linux Fundamentals Q" + std::to_string(i),
                    3, question.correctIndex);
                std::cout << "\n" << i + 1 << ". " << question.prompt << "\n\n";
                for (int j = 0; j < 3; ++j)
                {
                    std::cout << "   " << static_cast<char>('a' + j)
                        << ". " << question.options[order[j]] << "\n";
                }
                std::cout << "\n";
                int selectedPosition = ReadLetterAnswer(3);
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
            else if (RunModuleLesson(*lesson) && !selectedModule->IsCompleted())
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
        Pause();
    }
}
// ====================================
// Display Hands-On Labs
// ====================================

void TrainerApp::DisplayLabs() const
{
    std::cout << "\n====================================\n";
    std::cout << "           HANDS-ON LABS\n";
    std::cout << "====================================\n";

    for (int i = 0;
        i < static_cast<int>(labs.size());
        i++)
    {
        std::cout << i + 1 << ". ";

        if (labs[i].IsCompleted())
        {
            std::cout << "[COMPLETED] ";
        }
        else if (labs[i].IsUnlocked())
        {
            std::cout << "[AVAILABLE] ";
        }
        else
        {
            std::cout << "[LOCKED] ";
        }

        std::cout << labs[i].GetTitle() << std::endl;

        std::cout << "   Difficulty: "
            << labs[i].GetDifficulty()
            << std::endl;

        std::cout << "   Reward: "
            << labs[i].GetXPReward()
            << " XP\n\n";
    }

    std::cout << "0. Return to Main Menu\n";
    std::cout << "====================================\n";
}

// ====================================
// Open Hands-On Labs
// ====================================

void TrainerApp::OpenHandsOnLabs()
{
    bool viewingLabs = true;

    while (viewingLabs)
    {
        DisplayLabs();

        std::cout << "Select a lab: ";

        int choice = GetValidatedChoice(
            0,
            static_cast<int>(labs.size()));

        if (choice == 0)
        {
            viewingLabs = false;
            continue;
        }

        Lab* selectedLab = &labs[choice - 1];

        // Prevent access to locked labs.
        if (!selectedLab->IsUnlocked())
        {
            std::cout << "\n====================================\n";
            std::cout << "             LAB LOCKED\n";
            std::cout << "====================================\n";

            std::cout << selectedLab->GetTitle()
                << " is not available yet.\n";

            std::cout << "Complete earlier training first.\n";

            Pause();
            continue;
        }

        // Prevent duplicate XP rewards.
        if (selectedLab->IsCompleted())
        {
            selectedLab->DisplayLab();
            selectedLab->DisplayObjectives();

            std::cout << "\nYou already completed this lab.\n";
            std::cout << "No additional XP will be awarded.\n";

            Pause();
            continue;
        }

        // Launch the first simulated lab.
        if (choice == 1)
        {
            RunTerminalInvestigationLab(*selectedLab);
        }
    }
}

// ====================================
// Terminal Investigation Lab
// ====================================

void TrainerApp::RunTerminalInvestigationLab(Lab& lab)
{
    bool labRunning = true;
    std::string command;
    const std::string validationCode = GenerateValidationCode();

    lab.DisplayLab();

    std::cout << "\n====================================\n";
    std::cout << "        SAFE LAB ENVIRONMENT\n";
    std::cout << "====================================\n";

    std::cout
        << "You are inside a simulated "
        << "BugBountyTrainer workstation.\n";

    std::cout
        << "Commands entered here do NOT run "
        << "against your real computer.\n\n";

    std::cout
        << "Your goal is to investigate the "
        << "training directory.\n";

    std::cout << "\nUseful command:\n";
    std::cout << "help\n";
    std::cout << "====================================\n";

    while (labRunning)
    {
        std::cout << "\nBBT-LAB> ";

        if (!std::getline(std::cin, command))
        {
            throw std::runtime_error("Input stream closed.");
        }

        // ====================================
        // Help Command
        // ====================================

        if (command == "help")
        {
            std::cout << "\nAvailable simulated commands:\n";
            std::cout << "whoami\n";
            std::cout << "dir\n";
            std::cout << "type <filename>\n";
            std::cout << "submit <code>\n";
            std::cout << "status\n";
            std::cout << "exit\n";
        }

        // ====================================
        // Identify Current User
        // ====================================

        else if (command == "whoami")
        {
            std::cout << "bbt-training\\researcher\n";

            if (!lab.IsObjectiveCompleted(1))
            {
                lab.CompleteObjective(1);

                std::cout
                    << "[OBJECTIVE COMPLETE] "
                    << "Current user identified.\n";
            }
        }

        // ====================================
        // List Training Directory
        // ====================================

        else if (command == "dir")
        {
            std::cout << "\nDirectory of C:\\BBT-Lab\n\n";

            std::cout
                << "10/09/2026  06:00 AM    "
                << "<DIR>          logs\n";

            std::cout
                << "10/09/2026  06:00 AM             "
                << "94 training.txt\n";

            std::cout
                << "10/09/2026  06:00 AM             "
                << "38 notes.txt\n";

            if (!lab.IsObjectiveCompleted(2))
            {
                lab.CompleteObjective(2);

                std::cout
                    << "\n[OBJECTIVE COMPLETE] "
                    << "Training directory inspected.\n";
            }
        }

        // ====================================
        // Read Training File
        // ====================================

        else if (command == "type training.txt")
        {
            // Require the directory objective first.
            if (!lab.IsObjectiveCompleted(2))
            {
                std::cout
                    << "Investigate the directory first.\n";

                continue;
            }

            std::cout << "\nBUG BOUNTY TRAINER\n";
            std::cout << "Authorized Training File\n";
            std::cout << "Validation Code: " << validationCode << "\n";

            if (!lab.IsObjectiveCompleted(3))
            {
                lab.CompleteObjective(3);

                std::cout
                    << "\n[OBJECTIVE COMPLETE] "
                    << "training.txt inspected.\n";
            }

            // The researcher must manually submit the
            // validation code to complete Objective 4.
            if (!lab.IsObjectiveCompleted(4))
            {
                std::cout
                    << "\n[OBJECTIVE PENDING] "
                    << "Submit the validation code using:\n"
                    << "submit <code>\n";
            }
        }
        // ====================================
        // Submit Validation Code
        // ====================================
        else if (command.rfind("submit ", 0) == 0)
        {
            // Require the training file to be inspected first.
            if (!lab.IsObjectiveCompleted(3))
            {
                std::cout
                    << "\nInspect training.txt before "
                    << "submitting a validation code.\n";
            }
            else if (lab.IsObjectiveCompleted(4))
            {
                std::cout
                    << "\nValidation code already accepted.\n";
            }
            else
            {
                // Extract the submitted code.
                std::string submittedCode = command.substr(7);

                // Compare against the training file code.
                if (submittedCode == validationCode)
                {
                    lab.CompleteObjective(4);

                    std::cout
                        << "\n[OBJECTIVE COMPLETE] "
                        << "Validation code accepted!\n";
                }
                else
                {
                    std::cout
                        << "\nIncorrect validation code. "
                        << "Please try again.\n";
                }
            }
        }

        // ====================================
        // Optional Notes File
        // ====================================

        else if (command == "type notes.txt")
        {
            std::cout << "Hint: Inspect training.txt.\n";
        }

        // ====================================
        // Display Lab Progress
        // ====================================

        else if (command == "status")
        {
            lab.DisplayObjectives();
        }

        // ====================================
        // Exit Lab
        // ====================================

        else if (command == "exit")
        {
            labRunning = false;
        }

        else if (command.empty())
        {
            continue;
        }

        // ====================================
        // Invalid Lab Command
        // ====================================

        else
        {
            std::cout << "'"
                << command
                << "' is not a recognized lab command.\n";

            std::cout
                << "Type help to view available commands.\n";
        }

        // ====================================
        // Automatic Lab Completion
        // ====================================

        if (lab.AreAllObjectivesCompleted() &&
            !lab.IsCompleted())
        {
            bool completed = lab.CompleteLab();

            if (completed)
            {
                // Award the lab's XP once.
                researcher.AddXP(lab.GetXPReward());

                // ====================================
                // Connect Lab to Learning Module
                // ====================================

                             // Terminal Investigation is the required
                             // hands-on lab for Computer Fundamentals.
                if (lab.GetTitle() == "Terminal Investigation" &&
                    learningModules[1].IsUnlocked() &&
                    !learningModules[1].IsCompleted())
                {
                    learningModules[1].CompleteModule();

                    // Award the module XP bonus once.
                    if (learningModules[1].IsCompleted())
                    {
                        researcher.AddXP(
                            learningModules[1].GetXPReward());

                        std::cout << "\n====================================\n";
                        std::cout << "       LEARNING MODULE COMPLETE!\n";
                        std::cout << "====================================\n";

                        std::cout
                            << learningModules[1].GetTitle()
                            << " completed successfully!\n";

                        std::cout << "\nModule XP Bonus: "
                            << learningModules[1].GetXPReward()
                            << " XP\n";

                        std::cout
                            << "\nTerminal Investigation satisfied "
                            << "the required hands-on training.\n";

                        std::cout << "====================================\n";
                    }
                }

                std::cout << "\n====================================\n";
                std::cout << "            LAB COMPLETE!\n";
                std::cout << "====================================\n";

                std::cout << lab.GetTitle()
                    << " completed successfully.\n";

                std::cout
                    << "\nAll required objectives were validated.\n";

                std::cout << "\nXP Earned: "
                    << lab.GetXPReward()
                    << std::endl;

                std::cout << "Total XP: "
                    << researcher.GetTotalXP()
                    << std::endl;

                std::cout << "Available XP: "
                    << researcher.GetAvailableXP()
                    << std::endl;

                std::cout << "====================================\n";

                labRunning = false;
            }
        }
    }

    if (!lab.IsCompleted())
    {
        std::cout << "\nLab exited before completion.\n";

        std::cout
            << "Your completed objectives remain "
            << "available during this session.\n";
    }

    Pause();
}

// ====================================
// Display Training Challenges
// ====================================

void TrainerApp::DisplayChallenges() const
{
    std::cout << "\n====================================\n";
    std::cout << "       TRAINING CHALLENGES\n";
    std::cout << "====================================\n";

    for (int i = 0;
        i < static_cast<int>(challenges.size());
        i++)
    {
        std::cout << i + 1 << ". "
            << challenges[i].GetTitle()
            << std::endl;

        std::cout << "   Category: "
            << challenges[i].GetCategory()
            << std::endl;

        std::cout << "   Difficulty: "
            << challenges[i].GetDifficulty()
            << std::endl;

        std::cout << "   Reward: "
            << challenges[i].GetXPReward()
            << " XP\n";

        if (challenges[i].IsCompleted())
        {
            std::cout << "   Status: Completed\n";
        }
        else
        {
            std::cout << "   Status: Not Completed\n";
        }

        std::cout << std::endl;
    }

    std::cout << "====================================\n";
}

// ====================================
// Start Training
// ====================================

void TrainerApp::StartTraining()
{
    std::cout << "\n====================================\n";
    std::cout << "          START TRAINING\n";
    std::cout << "====================================\n";

    for (int i = 0;
        i < static_cast<int>(challenges.size());
        i++)
    {
        std::cout << i + 1 << ". "
            << challenges[i].GetTitle()
            << " ["
            << challenges[i].GetDifficulty()
            << "]";

        if (challenges[i].IsCompleted())
        {
            std::cout << " - Completed";
        }

        std::cout << std::endl;
    }

    std::cout << "0. Return to Main Menu\n";
    std::cout << "====================================\n";
    std::cout << "Choose a challenge: ";

    int choice = GetValidatedChoice(
        0,
        static_cast<int>(challenges.size()));

    if (choice == 0)
    {
        return;
    }

    Challenge* selectedChallenge =
        &challenges[choice - 1];

    selectedChallenge->DisplayChallenge();

    // Do not award XP for previously completed challenges.
    if (selectedChallenge->IsCompleted())
    {
        std::cout
            << "\nYou already completed this challenge.\n";

        return;
    }

    const std::vector<std::string>& options =
        selectedChallenge->GetAnswerOptions();

    // Find the answer's original position before shuffling its display order.
    int correctIndex = -1;
    for (int i = 0; i < static_cast<int>(options.size()); ++i)
    {
        if (selectedChallenge->IsCorrectAnswer(i + 1))
        {
            correctIndex = i;
            break;
        }
    }

    if (correctIndex < 0)
    {
        throw std::runtime_error("Challenge answer key is invalid.");
    }

    const std::vector<int> order = ShuffleAnswerPositions(
        "Challenge: " + selectedChallenge->GetTitle(),
        static_cast<int>(options.size()),
        correctIndex);

    std::cout << "\n1. " << selectedChallenge->GetQuestion() << "\n\n";
    for (int i = 0; i < static_cast<int>(options.size()); ++i)
    {
        std::cout << "   " << static_cast<char>('a' + i)
            << ". " << options[order[i]] << '\n';
    }
    std::cout << '\n';

    int selectedPosition = ReadLetterAnswer(static_cast<int>(options.size()));
    int answer = order[selectedPosition] + 1;

    if (selectedChallenge->IsCorrectAnswer(answer))
    {
        // Save the level before awarding XP.
        int oldLevel = researcher.GetLevel();

        // Mark the challenge as completed.
        selectedChallenge->CompleteChallenge();

        // Award challenge XP.
        researcher.AddXP(
            selectedChallenge->GetXPReward());

        std::cout << "\n====================================\n";
        std::cout << "        CHALLENGE COMPLETED!\n";
        std::cout << "====================================\n";

        std::cout << "Correct!\n";

        std::cout << "You earned "
            << selectedChallenge->GetXPReward()
            << " XP.\n";

        // ====================================
        // Automatic Learning Module Completion
        // ====================================

        // Level 0 requires:
        // 1. Authorization Basics
        // 2. Scope Basics
        //
        // Both must be completed before
        // the learning module can be finished.
        //
        // The module bonus is awarded only once.

        if (challenges[0].IsCompleted() &&
            challenges[1].IsCompleted() &&
            !learningModules[0].IsCompleted())
        {
            // Complete Learning Module 0.
            learningModules[0].CompleteModule();

            // Verify the module was completed.
            if (learningModules[0].IsCompleted())
            {
                // Award the module XP bonus.
                researcher.AddXP(
                    learningModules[0].GetXPReward());

                std::cout << "\n====================================\n";
                std::cout << "       LEARNING MODULE COMPLETE!\n";
                std::cout << "====================================\n";

                std::cout
                    << learningModules[0].GetTitle()
                    << " completed successfully!\n";

                std::cout << "\nModule XP Bonus: "
                    << learningModules[0].GetXPReward()
                    << " XP\n";

                std::cout
                    << "\nYou can now unlock "
                    << "Computer Fundamentals.\n";

                std::cout << "====================================\n";
            }
        }

        // ====================================
        // Display Updated Researcher Progress
        // ====================================

        std::cout << "\nTotal XP: "
            << researcher.GetTotalXP()
            << std::endl;

        std::cout << "Available XP: "
            << researcher.GetAvailableXP()
            << std::endl;

        // Check whether the researcher gained a level.
        if (researcher.GetLevel() > oldLevel)
        {
            std::cout << "\nLEVEL UP!\n";

            std::cout << "You are now Level "
                << researcher.GetLevel()
                << "!\n";
        }
    }
    else
    {
        std::cout << "\n====================================\n";
        std::cout << "          TRY AGAIN\n";
        std::cout << "====================================\n";

        std::cout << "That answer was not correct.\n";
        std::cout << "No XP was lost.\n";
    }
}
// ====================================
// Docker SQL Injection Training Menu
// ====================================

void TrainerApp::OpenDockerLabs()
{
    bool inMenu = true;

    while (inMenu)
    {
        std::cout << "\n====================================\n";
        std::cout << "       DOCKER TRAINING LAB\n";
        std::cout << "====================================\n";

        const bool connected = DockerLabClient::IsConnected();

        std::cout << "Connection: "
            << (connected ? "ONLINE" : "OFFLINE") << '\n';

        std::cout << "Server: 127.0.0.1:8086\n";

        std::cout << "====================================\n";
        std::cout << "1. Check Docker Connection\n";
        std::cout << "2. View SQL Injection Challenges\n";
        std::cout << "3. View Docker Lab Status\n";
        std::cout << "0. Return to Main Menu\n";
        std::cout << "====================================\n";
        std::cout << "Choice: ";

        const int choice = GetValidatedChoice(0, 3);

        switch (choice)
        {
        case 1:
        {
            if (DockerLabClient::IsConnected())
            {
                std::cout << "\nDocker connection successful!\n";
            }
            else
            {
                std::cout << "\nDocker connection failed.\n";
                std::cout << "Make sure the C++ container is running.\n";
            }

            Pause();
            break;
        }

        case 2:
        {
            std::string response;

            if (DockerLabClient::GetChallenges(response))
            {
                std::cout << "\nAvailable Docker Challenges:\n";
                std::cout << response << '\n';
            }
            else
            {
                std::cout << "\nUnable to retrieve challenges.\n";
            }

            Pause();
            break;
        }

        case 3:
        {
            std::string response;

            if (DockerLabClient::GetStatus(response))
            {
                std::cout << "\nDocker Lab Status:\n";
                std::cout << response << '\n';
            }
            else
            {
                std::cout << "\nUnable to retrieve Docker status.\n";
            }

            Pause();
            break;
        }

        case 0:
            inMenu = false;
            break;

        default:
            break;
        }
    }
}

// ====================================
// Main Menu Choice Handling
// ====================================

void TrainerApp::HandleChoice(int choice)
{
    switch (choice)
    {
    case 1:
        researcher.DisplayProfile();
        break;
    case 2:
        OpenLearningPath();
        break;
    case 3:
        OpenHandsOnLabs();
        break;
    case 4:
        StartTraining();
        break;
    case 5:
        DisplayChallenges();
        break;
    case 6:
        BrowseCategories();
        break;
    case 7:
        SaveProgress();
        break;
    case 8:
        LoadProgress();
        break;
    case 10:
    {
        sqlFundamentals.Run();

        if (sqlFundamentals.IsAssessmentComplete() &&
            !sqlFundamentals.IsRewardClaimed())
        {
            researcher.AddXP(150);
            sqlFundamentals.MarkRewardClaimed();

            std::cout << "\nSQL Fundamentals completion reward: 150 XP!\n";
            std::cout << "Save your progress to keep this reward.\n";
        }

        break;
    }
    case 11:
    {
        sqlInjection.Run();

        if (sqlInjection.IsAssessmentComplete() &&
            !sqlInjection.IsRewardClaimed())
        {
            researcher.AddXP(200);
            sqlInjection.MarkRewardClaimed();

            std::cout
                << "\nSQL Injection Stage 2 completion reward: 200 XP!\n";

            std::cout
                << "Save your progress to keep this reward.\n";
        }

        break;
    }
    case 12:
    {
        OpenDockerLabs();
        break;
    }
    case 13:
    {
        // Record completion before this academy visit so XP is awarded
        // only for modules newly completed during this session.
        const std::vector<SQLLesson>& lessons = sqlAcademy.GetLessons();
        std::vector<bool> previouslyCompleted;
        previouslyCompleted.reserve(lessons.size());
        for (const SQLLesson& lesson : lessons)
        {
            previouslyCompleted.push_back(lesson.completed);
        }

        sqlAcademy.Run();

        const std::vector<SQLLesson>& updatedLessons = sqlAcademy.GetLessons();
        for (std::size_t i = 0; i < updatedLessons.size(); ++i)
        {
            if (!previouslyCompleted[i] && updatedLessons[i].completed)
            {
                researcher.AddXP(updatedLessons[i].xpReward);
                std::cout << "\nSQL Academy: " << updatedLessons[i].title
                    << " completed! Earned " << updatedLessons[i].xpReward
                    << " XP.\n";
                std::cout << "Save your progress to keep this reward.\n";
            }
        }
        break;
    }
    case 9:
        running = false;
        std::cout << "\nThank you for using BugBountyTrainer!\n";
        std::cout << "Keep learning and test responsibly.\n";
        break;
    }
}

// ====================================
// Pause
// ====================================

void TrainerApp::Pause() const
{
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

// ====================================
// Run Application
// ====================================

void TrainerApp::DisplayStartupMenu() const
{
    std::cout << "\n====================================\n";
    std::cout << "        BUG BOUNTY TRAINER\n";
    std::cout << "====================================\n";
    std::cout << "1. New User\n";
    std::cout << "2. Load Saved Progress\n";
    std::cout << "3. Options\n";
    std::cout << "4. Delete Saved User\n";
    std::cout << "5. Exit\n";
    std::cout << "====================================\n";
}

void TrainerApp::OpenOptions()
{
    std::cout << "\n====================================\n";
    std::cout << "              OPTIONS\n";
    std::cout << "====================================\n";
    std::cout << "Input validation: Enabled\n";
    std::cout << "Saved progress is stored in the application folder.\n";
    Pause();
}
bool TrainerApp::SelectSavedUser()
{

    const std::vector<std::filesystem::path> saveFiles = FindSaveFiles(true);

    if (saveFiles.empty())
    {
        std::cout << "\nNo supported saved users found.\n";
        Pause();
        return false;
    }

    std::cout << "\nAvailable saved users:\n";
    for (int i = 0; i < static_cast<int>(saveFiles.size()); ++i)
    {
        std::cout << i + 1 << ". " << SavedUserLabel(saveFiles[i]) << '\n';
    }

    std::cout << "0. Return to startup menu\n";
    std::cout << "Choose a saved user: ";
    int choice = GetValidatedChoice(0, static_cast<int>(saveFiles.size()));

    if (choice == 0)
    {
        return false;
    }
    if (!SaveManager::LoadProgress(
        researcher,
        challenges,
        learningModules,
        sqlFundamentals,
        sqlInjection,
        sqlAcademy,
        saveFiles[choice - 1].string()))
    {
        std::cout << "\nUnable to load that save file.\n";
        
        return false;
    }

    std::cout << "\nProgress loaded for " << researcher.GetName() << ".\n";
     Pause();
     return true;
}

void TrainerApp::DeleteSavedUser()
{
    const std::vector<std::filesystem::path> saveFiles = FindSaveFiles(false);

    if (saveFiles.empty())
    {
        std::cout << "\nNo saved-user files found.\n";
        Pause();
        return;
    }

    std::cout << "\nSaved-user files available to delete:\n";
    for (int i = 0; i < static_cast<int>(saveFiles.size()); ++i)
    {
        std::cout << i + 1 << ". " << SavedUserLabel(saveFiles[i])
            << " (" << saveFiles[i].filename().string() << ")\n";
    }

    std::cout << "0. Cancel\n";
    std::cout << "Choose a saved user to delete: ";
    int choice = GetValidatedChoice(0, static_cast<int>(saveFiles.size()));

    if (choice == 0)
    {
        return;
    }

    const std::filesystem::path selectedFile = saveFiles[choice - 1];
    std::cout << "\nDelete " << SavedUserLabel(selectedFile) << "?\n";
    std::cout << "File: " << selectedFile.filename().string() << '\n';
    std::cout << "This permanently removes this save file.\n";
    std::cout << "1. Delete\n2. Cancel\nChoice: ";

    if (GetValidatedChoice(1, 2) != 1)
    {
        std::cout << "\nDeletion cancelled.\n";
        Pause();
        return;
    }

    std::error_code error;
    const bool deleted = std::filesystem::remove(selectedFile, error);

    if (deleted && !error)
    {
        std::cout << "\nSaved user deleted successfully.\n";
    }
    else
    {
        std::cout << "\nUnable to delete that save file.\n";
        if (error)
        {
            std::cout << error.message() << '\n';
        }
    }
    Pause();
}
bool TrainerApp::StartSession()
{
    while (running)
    {
        DisplayStartupMenu();

        std::cout << "Choose an option: ";
        int choice = GetValidatedChoice(1, 5);

        if (choice == 1)
        {
            std::string name;

            while (true)
            {
                std::cout << "\nEnter your researcher name: ";

                if (!std::getline(std::cin, name))
                {
                    throw std::runtime_error("Input stream closed.");
                }

                if (name.find_first_not_of(" \t") != std::string::npos)
                {
                    break;
                }

                std::cout << "Name cannot be empty.\n";
            }

            researcher = Researcher(name);

            std::cout << "\nNew researcher created successfully.\n";
            Pause();

            return true;
        }
        else if (choice == 2)
        {
            if (SelectSavedUser())
            {
                return true;
            }
        }
        else if (choice == 3)
        {
            OpenOptions();
        }
        else if (choice == 4)
        {
            DeleteSavedUser();
        }
        else if (choice == 5)
        {
            running = false;
            return false;
        }
    }

    return false;
}


void TrainerApp::Run()
{
    try
    {
        if (!StartSession())
        {
            return;
        }

        while (running)
        {
            DisplayMenu();
            int choice = GetValidatedChoice(1, 13);
            HandleChoice(choice);

            // These screens handle their own pauses.
            if (running && choice != 2 && choice != 3 && choice != 6 && choice != 10 && choice != 13)
            {
                Pause();
            }
        }
    }
    catch (const std::runtime_error& error)
    {
        std::cout << "\n" << error.what() << " Exiting BugBountyTrainer.\n";
        running = false;
    }
}

std::vector<std::string> TrainerApp::GetCategories() const
{
    std::vector<std::string> categories;

    for (const Challenge& challenge : challenges)
    {
        const std::string category = challenge.GetCategory();

        if (std::find(
            categories.begin(),
            categories.end(),
            category) == categories.end())
        {
            categories.push_back(category);
        }
    }

    return categories;
}
// ====================================
// Display Vulnerability Categories
// ====================================

void TrainerApp::DisplayCategories() const
{
    std::cout << "\n====================================\n";
    std::cout << "       VULNERABILITY CATEGORIES\n";
    std::cout << "====================================\n";
    const std::vector<std::string> categories = GetCategories();

    for (int i = 0; i < static_cast<int>(categories.size()); ++i)
    {
        std::cout << i + 1 << ". " << categories[i] << '\n';
    }

    std::cout << "\n0. Return to Main Menu\n";
    std::cout << "====================================\n";
}

// ====================================
// Display Challenges by Category
// ====================================

void TrainerApp::DisplayChallengesByCategory(const std::string& selectedCategory) const
{
    std::cout << "\n====================================\n";
    std::cout << "       CATEGORY: " << selectedCategory << '\n';
    std::cout << "====================================\n";

    bool found = false;
    for (const Challenge& challenge : challenges)
    {
        if (challenge.GetCategory() == selectedCategory)
        {
            found = true;
            std::cout << "\nChallenge: " << challenge.GetTitle() << '\n';
            std::cout << "Difficulty: " << challenge.GetDifficulty() << '\n';
            std::cout << "XP Reward: " << challenge.GetXPReward() << '\n';
            std::cout << "Status: " << (challenge.IsCompleted() ? "Completed" : "Not Completed") << '\n';
        }
    }

    if (!found)
    {
        std::cout << "\nNo challenges available in this category.\n";
    }
    std::cout << "====================================\n";
}

// ====================================
// Browse Vulnerability Categories
// ====================================

void TrainerApp::BrowseCategories()
{
    const std::vector<std::string> categories = GetCategories();

    bool browsing = true;
    while (browsing)
    {
        DisplayCategories();
        std::cout << "Select a category: ";
        int choice = GetValidatedChoice(0, static_cast<int>(categories.size()));
        if (choice == 0)
        {
            browsing = false;
        }
        else
        {
            DisplayChallengesByCategory(categories[choice - 1]);

            Pause();
        }
    }
}

// ====================================
// Save Researcher and Challenge Progress
// ====================================

void TrainerApp::SaveProgress()
{
    const std::string filename = SaveFilenameFor(researcher.GetName());

    std::cout << "\n====================================\n";
    std::cout << "          SAVE PROGRESS\n";
    std::cout << "====================================\n";

    // Save researcher information and challenges.
    if (SaveManager::SaveProgress(
        researcher,
        challenges,
        learningModules,
        sqlFundamentals,
        sqlInjection,
        sqlAcademy,
        filename))
    {
        std::cout << "\nProgress saved successfully!\n";
    }
    else
    {
        std::cout << "\nUnable to save progress.\n";
    }
}

// ====================================
// Load Researcher and Challenge Progress
// ====================================

void TrainerApp::LoadProgress()
{
    const std::string filename = SaveFilenameFor(researcher.GetName());

    std::cout << "\n====================================\n";
    std::cout << "          LOAD PROGRESS\n";
    std::cout << "====================================\n";

    // Restore researcher information and challenges.
    if (SaveManager::LoadProgress(
        researcher,
        challenges,
        learningModules,
        sqlFundamentals,
        sqlInjection,
        sqlAcademy,
        filename))
    {
        std::cout << "\nProgress restored successfully!\n";
    }
    else
    {
        std::cout << "\nUnable to load progress.\n";
    }
}


