# BugBountyTrainer — Milestone 3 Development and Refactoring

**Course:** Project and Portfolio I: Computer Science — Online  
**Project:** BugBountyTrainer  
**Milestone:** Week 3 / Milestone 3  
**Repository:** https://github.com/raymondsmith-ai/BugBountyTrainer

## Project Overview

BugBountyTrainer is a C++20 console application that teaches introductory ethical hacking and bug bounty concepts through learning modules, challenges, and hands-on exercises. Users maintain a researcher profile, earn experience points (XP), unlock training modules, and save their progress.

During Milestone 3, I focused on expanding the learning content while improving stability, maintainability, and progression tracking. Rather than simply adding more menu options, I worked on making the existing features more consistent and reliable.

## Features Added and Expanded

### Expanded Learning Content and Assessments

I added lessons and assessments for learning modules that previously had incomplete or placeholder content. I also developed SQL Fundamentals training with guided query practice and an independent assessment. This provides learners with activities that require applying concepts rather than only reading module descriptions.

### Researcher Profiles and Save/Load Improvements

I improved the saved-researcher workflow, including displaying saved user names, filtering unsupported save files, and allowing saved users to be deleted. I also integrated additional learning progress into the existing `SaveManager` system. These changes make it easier to resume training and reduce the risk of incorrectly restoring progress.

### Progression and XP Reliability

I improved completion checks across challenges, labs, and learning modules. Completed activities should not grant XP repeatedly. SQL Fundamentals progress and its one-time reward were added to persistent progress tracking, allowing completed work to remain recorded between sessions.

### Practical Training

I expanded the SQL Fundamentals activities and developed a local Docker/SQLite training proof of concept using fictional data. This work demonstrates the project's potential for more interactive laboratories. The larger SQL Injection Academy remains future development and is not required to consider the Milestone 3 console application complete.

## System Design Improvements

- **`TrainerApp`:** Continued organizing application menus, lesson access, assessment flow, and user feedback.
- **`Challenge` and assessment logic:** Used stored questions and answers to keep challenge content separate from repeated display and checking logic.
- **`SaveManager`:** Extended progress serialization and validation as new learning features were introduced.
- **`LearningModule` and lab progression:** Continued connecting prerequisites, completion state, and XP rewards across training activities.
- **Regression tests:** Added separate test coverage for researcher XP, challenge answers, labs, learning modules, and save/load behavior.

These changes build on the existing class structure instead of replacing the project with an entirely different application.

## Refactoring and Code Quality

### Removed Duplicate Category-Browsing Logic

I refactored category browsing to reduce duplicated code. Reusing shared behavior makes menu changes easier to maintain and helps prevent different parts of the program from displaying inconsistent information.

**Related commit:** `ce15f2d` — *Refactor category browsing to remove duplicate code*.

### Centralized Challenge Questions and Answers

I changed the training implementation to use questions and answers stored with challenges rather than handling the same information through repetitive training logic. This improves organization and makes it easier to add or revise challenges without duplicating as much code.

**Related commit:** `3414f09` — *Refactor training to use stored challenge questions and answers*.

### Improved Assessment Behavior

I added randomized assessment answer positions and reusable answer-input handling. The changes improve repeated assessment attempts and provide a more consistent interaction for the learner.

**Related commit:** `acc73e2` — *Add randomized assessments and improve Milestone 3 training*.

### Strengthened Save/Load Validation and Lab Completion Rules

I worked on preventing invalid or incomplete save data from changing an existing researcher's state. I also corrected lab completion behavior so that already completed labs do not report a new completion. This matters because repeated completion or a failed load could otherwise produce confusing progress or XP behavior.

**Related commit:** `b63f152` — *Add regression tests and fix repeated lab completion and failed loads*.

## Testing and Debugging

I used application-level testing while developing the lessons, assessments, menu flow, and progress features. Examples of scenarios tested during development include completing an SQL Fundamentals assessment, reviewing query-practice feedback, returning to completed activities, and checking one-time XP behavior.

I also added automated regression tests covering researcher XP boundaries, challenge answers, lab completion, module status, and save/load validation. The regression-testing document reports **50 checks with 0 failures** after fixes in a GCC C++20 test environment. This automated result does not replace a final Windows/Visual Studio rebuild and interactive menu test, which should be confirmed separately before the final course submission.

**Testing reference:** `docs/Regression-Testing.md`.

## Challenges and Why the Changes Matter

A significant challenge was adding new training features without disrupting saved progress or allowing XP to be awarded twice. I addressed this by adding completion checks, improving validation of saved information, and testing repeat attempts. Another challenge was keeping the growing `TrainerApp` and training logic understandable. Refactoring shared category behavior and challenge data helped reduce duplication and clarify responsibilities.

These improvements matter because BugBountyTrainer is intended to keep growing. A stable and organized foundation will make future lessons and laboratories easier to add and troubleshoot.

## Version Control and Project Workflow

I developed features and fixes through meaningful commits on the `dev` branch, including separate commits for assessment content, refactoring, regression tests, save/load improvements, and XP tracking. I used GitHub Issues and the Project board to organize development tasks.

The Milestone 3 development was reviewed and merged into `main` through **Pull Request #68 — Milestone 3: BugBountyTrainer Features and Stability Improvements**:

https://github.com/raymondsmith-ai/BugBountyTrainer/pull/68

The pull request is merged and closed. Additional work created after that merge should be treated separately when preparing the final academic submission.

## What I Learned

During Milestone 3, I gained more experience maintaining a growing C++ application. I learned that adding features is only part of development; preserving existing behavior, validating saved data, preventing repeated rewards, and documenting specific refactoring decisions are equally important. I also practiced using meaningful commits and testing to support code improvements.

## Next Steps

For Week 4, I plan to prioritize a final Visual Studio rebuild, interactive input-validation and save/load testing, documentation cleanup, and verification of GitHub Project board status and instructor access. Advanced training features—including a more extensive SQL Injection Academy, additional Docker labs, and external cybersecurity tools—will remain future development until the academic submission requirements are satisfied.
