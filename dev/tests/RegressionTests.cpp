#include "../include/Researcher.h"
#include "../include/Challenge.h"
#include "../include/Lab.h"
#include "../include/LearningModule.h"
#include "../include/SaveManager.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace
{
    int checks = 0;
    int failures = 0;

    void Check(bool condition, const std::string& description)
    {
        ++checks;
        if (!condition)
        {
            ++failures;
            std::cout << "[FAIL] " << description << '\n';
        }
    }

    Challenge MakeChallenge()
    {
        return Challenge("Authorization", "Training", "Ethics", "Easy", 100,
            "What must you have before testing?", {"Permission", "A password", "A scanner"}, 1);
    }

    LearningModule MakeModule(bool unlocked = false)
    {
        return LearningModule("Fundamentals", "Training", "Beginner", 1, 1, 125, 50, unlocked);
    }

    void TestResearcher()
    {
        Researcher user("Ray");
        Check(user.GetName() == "Ray" && user.GetLevel() == 1 &&
            user.GetTotalXP() == 0 && user.GetAvailableXP() == 0, "New researcher defaults");
        user.AddXP(0);
        user.AddXP(-10);
        Check(user.GetTotalXP() == 0 && user.GetAvailableXP() == 0, "Nonpositive XP ignored");
        user.AddXP(199);
        Check(user.GetLevel() == 1, "199 XP remains level 1");
        user.AddXP(1);
        Check(user.GetLevel() == 2 && user.GetTotalXP() == 200, "200 XP reaches level 2");
        user.AddXP(200);
        Check(user.GetLevel() == 3, "400 XP reaches level 3");
        user.AddXP(600);
        Check(user.GetLevel() == 6, "A large XP gain crosses multiple level boundaries");
        Check(!user.SpendXP(-1) && !user.SpendXP(1001), "Invalid and unaffordable purchases rejected");
        Check(user.GetAvailableXP() == 1000, "Rejected purchases preserve XP");
        Check(user.SpendXP(0) && user.SpendXP(1000), "Zero and exact-balance purchases accepted");
        Check(user.GetAvailableXP() == 0 && user.GetTotalXP() == 1000 &&
            user.GetLevel() == 6, "Spending preserves lifetime XP and level");
        Check(!user.RestoreProgress(0, 0, 0) && !user.RestoreProgress(1, -1, 0) &&
            !user.RestoreProgress(1, 100, 101), "Invalid restored progression rejected");
        Check(user.GetTotalXP() == 1000 && user.GetAvailableXP() == 0,
            "Rejected restore preserves current XP");
    }

    void TestChallenge()
    {
        Challenge challenge = MakeChallenge();
        Check(!challenge.IsCompleted(), "Challenge starts incomplete");
        Check(challenge.GetQuestion() == "What must you have before testing?" &&
            challenge.GetAnswerOptions().size() == 3, "Question and option getters preserve stored data");
        Check(challenge.IsCorrectAnswer(1) && !challenge.IsCorrectAnswer(2) &&
            !challenge.IsCorrectAnswer(0) && !challenge.IsCorrectAnswer(4), "Challenge answer validation");
        challenge.CompleteChallenge();
        challenge.CompleteChallenge();
        Check(challenge.IsCompleted(), "Repeated challenge completion preserves completed state");
        challenge.RestoreCompletion(false);
        Check(!challenge.IsCompleted(), "Challenge completion can be restored");
    }

    void TestLab()
    {
        Lab empty("Empty", "Training", "Easy", 150, true);
        Check(!empty.AreAllObjectivesCompleted() && !empty.CompleteLab(),
            "A lab with no objectives cannot complete");
        Lab lab("Terminal", "Training", "Easy", 150, false);
        lab.AddObjective("Identify user");
        lab.AddObjective("Read file");
        Check(!lab.CompleteLab(), "Locked lab cannot complete");
        Check(!lab.CompleteObjective(0) && !lab.CompleteObjective(-1) &&
            !lab.CompleteObjective(3), "Invalid objective numbers rejected");
        Check(lab.CompleteObjective(1), "First objective completion succeeds");
        Check(!lab.CompleteObjective(1), "Duplicate objective completion rejected");
        Check(!lab.AreAllObjectivesCompleted(), "Partial objectives do not complete lab");
        Check(lab.CompleteObjective(2) && lab.AreAllObjectivesCompleted(), "All objectives tracked");
        Check(!lab.CompleteLab(), "Completed objectives do not bypass a locked lab");
        lab.UnlockLab();
        Check(lab.CompleteLab() && lab.IsCompleted(), "Unlocked lab completes with all objectives");
        Check(!lab.CompleteLab(), "Repeating a completed lab does not report a new completion");
    }

    void TestModule()
    {
        LearningModule module = MakeModule();
        Check(!module.IsUnlocked() && !module.IsCompleted(), "Module starts locked and incomplete");
        module.CompleteModule();
        Check(!module.IsCompleted(), "Locked module cannot complete");
        module.UnlockModule();
        Check(module.IsUnlocked(), "Module unlock changes its state");
        module.CompleteModule();
        module.CompleteModule();
        Check(module.IsCompleted(), "Module completion remains completed on repeat");
        module.RestoreProgress(false, false);
        Check(!module.IsUnlocked() && !module.IsCompleted(), "Locked module state restores");
        module.RestoreProgress(false, true);
        Check(module.IsUnlocked() && module.IsCompleted(), "Restored completed module is unlocked");
    }

    class TemporaryFiles
    {
    public:
        std::filesystem::path directory;

        TemporaryFiles()
        {
            const auto base = std::filesystem::temp_directory_path();
            bool created = false;
            for (int attempt = 0; attempt < 100 && !created; ++attempt)
            {
                directory = base / ("bbt-regression-" + std::to_string(std::random_device{}()));
                created = std::filesystem::create_directory(directory);
            }
            if (!created)
            {
                throw std::runtime_error("Cannot create a temporary test directory.");
            }
        }

        ~TemporaryFiles()
        {
            std::error_code error;
            std::filesystem::remove(directory / "roundtrip.txt", error);
            std::filesystem::remove(directory / "invalid.txt", error);
            std::filesystem::remove(directory, error);
        }
    };

    void TestSaveLoad()
    {
        TemporaryFiles files;

        SQLFundamentals sqlFundamentals;
        SQLInjection sqlInjection;
        SQLAcademy sqlAcademy;

        Researcher original("Ray Smith");
        original.AddXP(450);
        original.SpendXP(50);
        std::vector<Challenge> challenges{MakeChallenge()};
        challenges[0].CompleteChallenge();
        std::vector<LearningModule> modules{MakeModule(true), MakeModule(false)};
        modules[0].CompleteModule();

        const std::string filename = (files.directory / "roundtrip.txt").string();
        Check(SaveManager::SaveProgress(
            original, challenges, modules,
            sqlFundamentals, sqlInjection, sqlAcademy, filename),
            "Save succeeds");

        Researcher loaded("Before load");
        SQLFundamentals loadedSQLFundamentals;
        SQLInjection loadedSQLInjection;
        SQLAcademy loadedSQLAcademy;
        std::vector<Challenge> loadedChallenges{MakeChallenge()};
        std::vector<LearningModule> loadedModules{MakeModule(), MakeModule(true)};

        Check(SaveManager::LoadProgress(
            loaded, loadedChallenges, loadedModules,
            loadedSQLFundamentals, loadedSQLInjection, loadedSQLAcademy, filename),
            "Load succeeds");
        Check(loaded.GetName() == "Ray Smith" && loaded.GetLevel() == 3 &&
            loaded.GetTotalXP() == 450 && loaded.GetAvailableXP() == 400,
            "Name and spent XP round-trip");
        Check(loadedChallenges[0].IsCompleted() && loadedModules[0].IsCompleted() &&
            loadedModules[0].IsUnlocked() && !loadedModules[1].IsUnlocked(),
            "Challenge and module states round-trip");

        Check(SaveManager::LoadProgress(
            loaded, loadedChallenges, loadedModules,
            loadedSQLFundamentals, loadedSQLInjection, loadedSQLAcademy, filename) &&
            loaded.GetTotalXP() == 450 && loaded.GetAvailableXP() == 400,
            "Repeated loading does not award XP");

        Check(loadedSQLAcademy.GetLessons().size() == sqlAcademy.GetLessons().size(),
            "SQL Academy lesson count round-trips");
        bool academyInitiallyIncomplete = true;
        for (const SQLLesson& lesson : loadedSQLAcademy.GetLessons())
        {
            if (lesson.completed)
            {
                academyInitiallyIncomplete = false;
            }
        }
        Check(academyInitiallyIncomplete, "Incomplete SQL Academy progress round-trips");

        const std::vector<std::string> invalidSaves{
            "BBT_SAVE_V1\nOther\n",
            "BBT_SAVE_V2\nOther\n",
            "BBT_SAVE_V2\nOther\n3\n450\n400\n9\n",
            "BBT_SAVE_V2\nOther\n3\n450\n400\n1\n7\n",
            "BBT_SAVE_V2\nOther\n3\n450\n400\n1\n1\n2\n1 1\n",
            "BBT_SAVE_V2\nOther\n3\n450\n451\n1\n1\n2\n1 1\n0 0\n"
        };
        const std::string invalid = (files.directory / "invalid.txt").string();
        for (std::size_t i = 0; i < invalidSaves.size(); ++i)
        {
            std::ofstream(invalid) << invalidSaves[i];
            Check(!SaveManager::LoadProgress(
                loaded, loadedChallenges, loadedModules,
                loadedSQLFundamentals, loadedSQLInjection, loadedSQLAcademy, invalid),
                "Malformed save rejected, case " + std::to_string(i + 1));
            Check(loaded.GetName() == "Ray Smith" && loaded.GetTotalXP() == 450 &&
                loaded.GetAvailableXP() == 400 && loadedChallenges[0].IsCompleted() &&
                loadedModules[0].IsCompleted() && !loadedModules[1].IsUnlocked(),
                "Rejected load preserves current state, case " + std::to_string(i + 1));
        }
    }
}

int main()
{
    try
    {
        TestResearcher();
        TestChallenge();
        TestLab();
        TestModule();
        TestSaveLoad();
    }
    catch (const std::exception& error)
    {
        ++failures;
        std::cout << "[ERROR] " << error.what() << '\n';
    }
    std::cout << "\nChecks: " << checks << " | Failures: " << failures << '\n';
    return failures == 0 ? 0 : 1;
}
