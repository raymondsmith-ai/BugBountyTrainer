# BugBountyTrainer

BugBountyTrainer is a C++ console application designed as a safe, simulated cybersecurity and bug bounty training environment.

The application allows users to create a researcher profile, complete cybersecurity training challenges, earn XP, level up, follow a structured learning path, and practice concepts through simulated hands-on labs.

## Project Goals

* Practice object-oriented programming
* Create a persistent menu-driven console application
* Use multiple interacting classes
* Practice file separation using header and source files
* Add input validation and clear user feedback
* Build a structured cybersecurity learning path
* Create safe simulated hands-on training labs
* Practice Git and GitHub development workflows

## Current Features

* Researcher profile system
* Researcher level and XP tracking
* Total XP and available XP
* Training challenge system
* Multiple training challenges
* Vulnerability categories
* Challenge difficulty levels
* Challenge completion tracking
* Prevention of duplicate XP rewards
* Progressive Learning Path
* Learning module prerequisites
* XP-based module unlocking
* Hands-On Labs menu
* Terminal Investigation simulated lab
* Lab objective tracking
* Learning module and lab integration
* Main menu navigation
* Input validation and improved error feedback
* Multiple C++ classes using separate header and source files

## Current Progress

### Week 1 / Milestone 1

Completed:

* Initial application structure
* Researcher class
* Challenge class
* TrainerApp class
* Working main menu
* Researcher profile display
* Training challenge display
* Challenge completion system
* XP reward system
* Project testing
* GitHub Project board setup
* GitHub Issues and milestone planning

### Week 2 / Milestone 2

Completed:

* Multiple training challenges
* Vulnerability categories
* Challenge difficulty levels
* Improved XP and level progression
* Total XP and available XP tracking
* Progressive Learning Path
* Learning module prerequisites
* XP-based module unlocking
* LearningModule class
* Lab class
* Hands-On Labs menu
* Terminal Investigation simulated lab
* Lab objective validation
* Learning module and lab integration
* Improved menu input feedback
* Milestone 2 testing and documentation

## Planned Development

### Week 3 / Milestone 3

* Expand hands-on training activities
* Add additional simulated labs
* Continue improving researcher progression
* Add tools and inventory features
* Add additional researcher statistics

### Week 4 / Milestone 4

* Add save and load functionality
* Complete application testing and bug fixes
* Final documentation
* Final project cleanup

## Technologies

* C++
* C++20
* Visual Studio
* Git
* GitHub
* GitHub Projects

## Development Workflow

Development work is completed on the `dev` branch and merged into `main` through Pull Requests.

The GitHub Project board uses:

**Backlog → To Do → In Progress → Done**

---

## Milestone 1 Project Stand-Up

### Overview

During Milestone 1, I worked on building the foundation of BugBountyTrainer, a C++ console application for practicing bug bounty and cybersecurity concepts. I created the project structure, built the Researcher and Challenge classes, added the TrainerApp class to manage program flow, and created a working menu system. I also tested the challenge completion and XP system and organized the project using Git and GitHub.

### Challenges

One of the main challenges I encountered was organizing the project files correctly and making sure the header and source files were in the proper folders. I also had to fix include paths after moving files between the `src` and `include` folders. I addressed these problems by checking the actual file locations, correcting the include paths, rebuilding the project frequently, and testing each change before moving forward.

### Accomplishments

I improved my understanding of organizing a C++ project across multiple classes and files instead of placing everything inside `main()`. I also gained more experience using Git and GitHub to manage branches, commits, Issues, and my Project board. My program had a working Researcher profile, training challenge system, XP rewards, challenge completion tracking, and menu flow.

### Next Steps

For Milestone 2, I planned to expand the training challenge system by adding more challenges, vulnerability categories, difficulty levels, and improved XP and level progression. I also planned to improve input validation and continue keeping the code organized as the project grew.

---

## Milestone 2 Project Stand-Up

### Overview

During Milestone 2, I expanded BugBountyTrainer from a basic challenge system into a more structured cybersecurity training application. I added a progressive Learning Path, XP-based module unlocking, module prerequisites, and a Hands-On Labs system. I also created the Terminal Investigation lab, which allows the user to practice basic investigation commands inside a simulated environment.

### Challenges

One challenge I encountered was connecting the different progression systems together. The program needed to recognize when a hands-on lab had already been completed before its related learning module was unlocked. I updated the program so completed lab requirements are recognized correctly and the user's learning progression can continue.

I also worked on improving input validation. Instead of displaying only generic error messages, the program now explains when a number is required and tells the user the valid selection range.

### Accomplishments

I created the `LearningModule` and `Lab` classes and connected them to the existing `TrainerApp`, `Researcher`, and `Challenge` systems. The program now tracks total XP separately from available XP, supports module prerequisites and XP costs, tracks lab objectives, awards XP for completed activities, and prevents duplicate XP rewards.

I also successfully tested the main menu, Learning Path, module unlocking, challenge progression, Terminal Investigation lab, objective tracking, invalid input handling, and the connection between lab completion and learning module completion.

### Next Steps

For the next milestone, I plan to continue expanding the training content and hands-on activities. I want to add more simulated labs, continue developing the later learning modules, improve researcher progression, and begin working on additional tools and inventory features.

## Author

Raymond Smith
