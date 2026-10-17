# BugBountyTrainer regression tests

This update addresses the regression-testing issue using the current dev branch.

## Install

Copy the dev and docs folders from this update into your BugBountyTrainer repository root, merging folders. The only existing source files replaced are dev/src/Lab.cpp and dev/src/SaveManager.cpp. The tests and this document are new.

Do not add RegressionTests.cpp to the existing Visual Studio application project: it has a separate main() and is compiled into a separate test executable by the runner.

Open Developer PowerShell for Visual Studio, change to the repository root, and run:

```powershell
& .\dev\tests\RunRegressionTests.ps1
```

If local script execution is blocked by your computer's policy, report the exact message rather than changing policy.

Expected final result:

```text
Checks: 50 | Failures: 0
```

Messages such as Invalid researcher data and Unsupported save file format are expected during rejection tests. A failure is marked [FAIL] or [ERROR], and the runner stops with an error.

The runner builds in a new temporary directory. File-I/O tests use their own temporary directory and never open or overwrite real researcher_save files.

## Automated coverage

| Area | Checks |
| --- | --- |
| Researcher | Initial state; nonpositive XP; 199/200/400 XP boundaries; multiple level gains; invalid, zero, and exact-balance spending; invalid restore rejection |
| Challenge | Stored question/options; correct/incorrect/out-of-range answers; completion and restored completion |
| Lab | Empty/locked/partial labs; invalid objective numbers; repeated objectives; first completion; repeated completion rejection |
| Learning module | Locked completion rejection; unlocking; completion; restored status |
| Save/load | Name with spaces; total/spendable XP; challenge/module status; repeated load without XP gain; unsupported/truncated/malformed data; state preserved after load rejection |

## Defects reproduced and fixed

The unmodified dev sources produced 50 checks with 6 failures. After the two fixes, the same tests produced 50 checks with 0 failures using GCC with C++20 and warnings enabled.

1. Lab::CompleteLab() previously returned true for an already-completed lab. It now rejects repeat completion. The caller must still award XP only when a first completion succeeds.
2. SaveManager::LoadProgress() previously assigned the saved name before validating the rest of the file. It now assigns the name after the complete file and researcher progression validate, preserving current state when a load is rejected.

A Windows/MSVC run and a Visual Studio application rebuild must still be performed by the project owner before closing the issue.

## Application-level checks still required

The automated checks exercise the real classes; they do not call the private TrainerApp menu functions or simulate the terminal command loop.

| Scenario | Expected result |
| --- | --- |
| Wrong challenge answer | No completion or XP reward |
| Correct challenge answer followed by repeat selection | XP awarded once |
| Terminal lab incomplete or wrong validation code | Lab remains incomplete, no lab reward |
| Complete terminal lab, then revisit during the same session | No duplicate lab/module XP |
| Unlock next module without prerequisites, level, or available XP | Unlock refused; XP unchanged |
| Valid module purchase | Spendable XP decreases by unlock cost; lifetime XP unchanged |
| Restart after completing and saving a lab | Check lab status and duplicate reward behavior; this is a known follow-up gap because BBT_SAVE_V2 does not serialize labs |

Do not close the duplicate-XP issue solely on these class tests: lab progress persistence after restart is not fixed by this update.
