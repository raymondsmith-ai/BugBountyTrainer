# Milestone 2 Project Planning Worksheet

> Use this worksheet to plan the next phase of your project **before you begin coding**

> Be clear, specific, and intentional—this will guide your development this week.

---

## 📌 Project Overview

**Project Name:**

→ BugBountyTrainer

**What does your program currently do? (1–3 sentences)**

→ BugBountyTrainer is a C++ console application that introduces users to ethical hacking and bug bounty concepts through training challenges. The program currently allows a user to navigate menus, select training challenges, view challenge information, complete challenges, earn XP, and track researcher progress.

---

## 🔍 Current Progress Check

**What is working right now?**

→ The main console menu is working, and the program successfully builds and runs. The `TrainerApp` class manages the main program flow, the `Researcher` class stores the user's name, level, and XP, and the `Challenge` class stores training challenge information such as title, description, category, difficulty, XP reward, and completion status.

The program currently includes multiple training challenges such as Authorization Basics, Scope Basics, and Input Validation Basics. The user can view challenges, select them, and interact with the training system.

**What is NOT working or incomplete?**

→ The program does not yet have a structured learning path that guides users from beginner topics to more difficult cybersecurity topics. Challenges currently exist as individual activities, but they are not organized into a clear progression.

The program also does not yet have prerequisite requirements or module unlocking. Future features such as hands-on sandbox environments, virtual machines, guided hacking labs, and advanced training environments are planned but are outside the scope of this milestone.

**What feels confusing or messy in your code?**

→ As the project grows, the `TrainerApp` class could become responsible for too many different parts of the program. I want to improve the organization of the program so learning content, challenges, researcher progress, and menu navigation each have clearer responsibilities.

I also want to make sure new features are added through separate classes instead of placing too much logic inside the main application class.

---

## 🚀 Feature Planning

List the features you plan to add or improve this week.

### Feature 1

**Name:**

→ Progressive Learning Path

**What does this feature do?**

→ This feature will organize the training content into an ordered learning path that begins with basic cybersecurity concepts and gradually becomes more difficult.

The learning path will begin with topics such as rules, ethics, authorization, computer fundamentals, Linux fundamentals, networking, and web fundamentals. Later levels will eventually introduce reconnaissance, web vulnerabilities, bug bounty methodology, and advanced security topics.

Users will complete earlier learning modules before progressing to more difficult modules.

**Why is this feature important?**

→ This feature is important because BugBountyTrainer is intended to teach users from complete beginner level through more advanced ethical hacking concepts. A structured progression will help prevent users from jumping into advanced material before learning the necessary fundamentals.

Each level will build on knowledge from the previous level.

---

### Feature 2

**Name:**

→ Learning Module System

**What does this feature do?**

→ This feature will introduce a new `LearningModule` class that represents a section of the learning path.

Each module will contain information such as:

* Module title
* Description
* Difficulty
* Module level
* Required level
* XP reward
* Completion status
* Unlock status

The program will display learning modules in order from easiest to most difficult.

**Why is this feature important?**

→ This feature gives the learning path a clear structure and makes it easier to expand the program in the future.

Instead of storing all training content directly inside the main application, learning modules can be managed as individual objects. This will make the project more organized and scalable.

---

### Feature 3

**Name:**

→ XP-Based Module Unlocking and Progression

**What does this feature do?**

→ This feature will control how users unlock new learning modules. Modules will be arranged from beginner to advanced, and the user must complete the previous module before the next module becomes available.

Completing lessons and challenges will reward XP. Users will then be able to spend earned XP to unlock the next learning module.

The system may track both total XP and available XP. Total XP represents the user's overall experience and progress, while available XP can be spent to unlock additional learning content.

For example:

Complete Level 2 → Earn XP → Spend XP → Unlock Level 3 → Complete Level 3 → Earn more XP → Unlock Level 4.

**Why is this feature important?**

→ This system gives the learner a stronger sense of progression and makes completing training activities feel rewarding. It also prevents users from immediately skipping to advanced cybersecurity material before completing the required beginner concepts.

Using XP to unlock modules adds a game-like progression system while still maintaining an ordered educational path from beginner to advanced.

---

## 🧩 System Design Updates

**Will you need to create any new classes? If so, which ones?**

→ Yes. I plan to create a new `LearningModule` class.

The `LearningModule` class will store information about each part of the learning path, including the title, description, difficulty, level requirement, XP reward, unlock status, and completion status.

Future versions of the project may add classes such as `Lesson`, `Lab`, or `LearningPath`, but those are not required for this milestone.

**Will you modify any existing classes? How?**

→ Yes.

The `TrainerApp` class will be updated to include a Learning Path menu and manage the collection of learning modules.

The `Researcher` class may be updated so the user's XP and level can be used to determine which learning modules are available.

The existing `Challenge` class will remain part of the program and will continue handling individual training challenges.

**What data structures will you use (vectors, 2D vectors, etc.)?**

→ I plan to use a `std::vector<LearningModule>` to store the learning modules.

The vector will allow the program to keep the modules in a specific order from beginner to advanced.

I will continue using vectors for groups of challenges or other content when needed.

---

## 🔄 Program Flow

**Describe how a user interacts with your program:**

1. Program starts →
   The program displays the BugBountyTrainer main menu and the user's current researcher information.

2. User chooses →
   The user selects an option such as Learning Path, Training Challenges, Researcher Profile, Progress, or Exit.

3. Program responds →
   If the user selects Learning Path, the program displays the available modules in order from easiest to most difficult. Completed, available, and locked modules will be clearly identified.

4. Loop/next step →
   The user can select an available module, complete training activities, earn XP, and return to the menu. Completing required modules allows the user to unlock more difficult parts of the learning path.

---

## 🎯 Usability Improvements

How will you make your program easier to use this week?

* **Clearer prompts:**

→ Menus will clearly explain which number the user should enter and what each option does. Learning modules will display their title, difficulty, level requirement, and completion status.

* **Better error handling:**

→ The program will validate menu input and prevent invalid selections from causing unexpected behavior. If the user enters an invalid option, the program will display a helpful message and allow the user to try again.

* **Improved menu/navigation:**

→ The main menu will be reorganized so users can easily move between the Learning Path, Training Challenges, Researcher Profile, Progress, and Exit options.

The Learning Path menu will display content in a clear order from beginner to advanced.

---

## ⚠️ Potential Challenges

**What do you think will be the hardest part this week?**

→ The hardest part will likely be connecting the new `LearningModule` system with the existing `TrainerApp` and `Researcher` classes without making the program overly complicated.

I will also need to make sure locked and unlocked modules behave correctly and that the learning path stays in the correct order.

**What is your plan if you get stuck?**

→ I will work on one feature at a time and rebuild the program frequently.

If I encounter problems, I will:

* Read compiler and error messages carefully
* Test smaller sections of the program
* Review course material
* Compare header declarations with `.cpp` implementations
* Use debugging tools when needed
* Research the specific programming concept
* Ask questions if I am still unable to solve the problem

---

## 📈 Level Up Goal

**What skill are you focusing on improving this week?**

→ Class design and program organization.

**What will you do to improve it?**

→ I will practice separating different responsibilities into appropriate classes instead of putting most of the program logic in one place.

I will review object-oriented programming concepts, study how classes interact with each other, and test each new feature as I add it.

I will also review my code after each feature to determine whether the logic belongs in `TrainerApp`, `Researcher`, `Challenge`, or the new `LearningModule` class.

---

## 🗓️ Task Breakdown (GitHub Issues Planning)

List the tasks you plan to create as GitHub Issues:

* [ ] Create `LearningModule` class
* [ ] Add progressive Learning Path menu
* [ ] Add module unlocking and difficulty progression
* [ ] Improve menu navigation and input validation

---

## 🔥 Final Check

Before you start coding, ask yourself:

* [x] Do I know what I’m building this week?
* [x] Do I know where to start?
* [x] Did I break my work into small tasks?

If yes → start coding 🚀

If no → refine your plan first

---

## 😈 Final Thought

> Plan it now… or debug it later.
