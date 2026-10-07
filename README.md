# BugBountyTrainer

BugBountyTrainer is a C++ console application designed to teach users the fundamentals of bug bounty research and cybersecurity in a safe, simulated training environment.

Users can create a researcher profile, complete fictional cybersecurity training challenges, earn XP, level up, and track their progress without interacting with real-world systems.

## Project Goals

- Practice object-oriented programming
- Build a menu-driven C++ console application
- Use multiple interacting classes
- Organize code using separate header and source files
- Create a cybersecurity training challenge system
- Add user input validation
- Add XP and level progression
- Track challenge completion
- Practice Git and GitHub development workflows
- Continue expanding the application through weekly milestones

## Current Features

- Researcher profile system
- Researcher name, level, and XP tracking
- Main menu navigation
- Menu input validation
- Menu choice range validation
- Multiple training challenges
- Challenge titles and descriptions
- Challenge difficulty levels
- Challenge XP rewards
- Multiple-choice challenge questions
- Challenge completion tracking
- Prevention of duplicate XP rewards
- XP and level progression
- Training challenge selection
- Ability to retry incorrectly answered challenges
- TrainerApp class for program flow
- Separate `.h` and `.cpp` files

## Training Challenges

BugBountyTrainer currently includes multiple cybersecurity training challenges.

### Authorization Basics

**Difficulty:** Easy  
**XP Reward:** 100 XP

Teaches users why authorization must be confirmed before performing security testing.

### Scope Basics

**Difficulty:** Easy  
**XP Reward:** 150 XP

Teaches users why bug bounty program scope must be followed and why unauthorized targets should not be tested.

### Input Validation Basics

**Difficulty:** Medium  
**XP Reward:** 200 XP

Introduces the importance of validating user input and preventing unexpected data from being processed.

## XP and Level System

Researchers begin at:

- Level 1
- 0 XP

Completing challenges awards XP based on the challenge.

The application checks the researcher's XP after completing a challenge and automatically increases the researcher's level when the required XP threshold is reached.

Researchers currently gain a new level every 200 XP.

Completed challenges cannot award XP more than once.

## Input Validation

The application validates user input before processing menu selections.

The program handles:

- Letters entered instead of numbers
- Invalid input types
- Numbers outside the allowed menu range
- Invalid challenge selections
- Invalid answer selections

If invalid input is entered, the input stream is cleared and the user is asked to enter another selection instead of allowing the menu loop to fail.

## Current Progress

### Week 1 / Milestone 1

Completed:

- Initial application structure
- Researcher class
- Challenge class
- TrainerApp class
- Working main menu
- Researcher profile display
- Initial training challenge system
- Challenge completion system
- XP reward system
- GitHub Project board setup
- GitHub Issues
- Weekly milestone planning
- Project folder organization
- Git and GitHub workflow setup

### Week 2 / Milestone 2

Completed:

- Improved main menu input validation
- Added menu choice range validation
- Added multiple training challenges
- Added challenge difficulty levels
- Added multiple-choice challenge questions
- Added XP and level progression
- Added duplicate XP prevention
- Connected the training system to the main menu
- Added challenge selection
- Added challenge completion status
- Added retry support for incorrect answers

Currently Developing:

- Vulnerability categories
- Researcher progress tracking
- Additional training content

## Planned Development

### Week 2 / Milestone 2

- Add vulnerability categories
- Expand researcher progress tracking
- Continue adding training challenges
- Continue testing menu and challenge input

### Week 3 / Milestone 3

- Add tools and inventory system
- Add researcher statistics
- Expand challenge completion tracking
- Add additional training content

### Week 4 / Milestone 4

- Add save and load functionality
- Complete application testing
- Fix remaining bugs
- Complete project documentation
- Final project cleanup

## Program Flow

The current application flow is:

```text
Main Menu
    |
    +-- View Researcher Profile
    |
    +-- Start Training
    |       |
    |       +-- Select Challenge
    |       |
    |       +-- View Challenge Information
    |       |
    |       +-- Answer Question
    |       |
    |       +-- Earn XP
    |       |
    |       +-- Update Level
    |
    +-- View Challenges
    |
    +-- Exit
