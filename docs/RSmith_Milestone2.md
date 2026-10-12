# BugBountyTrainer Milestone 2 Build Prototype

## Project Overview

BugBountyTrainer is a C++ console application designed to introduce users to ethical hacking and bug bounty concepts through structured learning modules, training challenges, XP progression, and simulated hands-on labs.

During Milestone 2, I focused on expanding the original training challenge system into a more structured learning experience. I also improved program navigation, input validation, progression tracking, and user feedback.

## Features Added

### Progressive Learning Path

I added a Learning Path that organizes training topics from beginner to advanced levels. Learning modules can have level requirements, prerequisite modules, XP rewards, and XP unlock costs.

The Learning Path currently includes topics such as:

- Rules, Ethics & Authorization
    
- Computer Fundamentals
    
- Linux Fundamentals
    
- Networking Fundamentals
    
- Web Fundamentals
    
- Reconnaissance
    
- Web Vulnerability Fundamentals
    
- Bug Bounty Methodology
    

### XP and Progression Improvements

The researcher progression system now tracks both total XP and available XP.

Total XP is used for researcher level progression, while available XP can be spent to unlock learning modules. Spending available XP does not remove XP that has already contributed toward the researcher's level.

The program also prevents completed challenges, modules, and labs from repeatedly awarding the same XP.

### Hands-On Labs

I added a hands-on lab system that allows users to practice concepts through simulated activities.

The first implemented lab is Terminal Investigation. This lab simulates a command-line investigation in a controlled training environment.

The user can use commands such as:

- `help`
    
- `whoami`
    
- `dir`
    
- `type <filename>`
    
- `status`
    
- `exit`
    

The lab tracks objectives and automatically completes when all required objectives have been finished.

### Learning Module and Lab Integration

I connected the hands-on lab system to the Learning Path.

Completing Terminal Investigation can satisfy the hands-on lab requirement for Computer Fundamentals. The program also handles the situation where the lab was completed before the learning module was unlocked.

This allows progression between different parts of the application to remain consistent.

## Code Structure Updates

I expanded the object-oriented structure of BugBountyTrainer by adding new classes and responsibilities.

### TrainerApp

`TrainerApp` continues to control the main program flow, menus, user selections, training activities, and navigation between different sections of the application.

### Researcher

`Researcher` tracks the researcher's name, level, total XP, and available XP.

### Challenge

`Challenge` represents training challenges and stores information such as the title, description, category, difficulty, XP reward, and completion status.

### LearningModule

I added the `LearningModule` class to manage learning path modules, including:

- Module titles and descriptions
    
- Difficulty
    
- Required researcher level
    
- XP rewards
    
- XP unlock costs
    
- Unlock status
    
- Completion status
    

### Lab

I added the `Lab` class to manage hands-on training labs, including:

- Lab information
    
- Objectives
    
- Objective completion
    
- Unlock status
    
- Completion status
    
- XP rewards
    

Separating these responsibilities into classes made the program easier to organize and expand.

## Usability Improvements

I improved the usability of the application by making input error messages more specific.

Previously, invalid input displayed generic messages such as `Invalid input` or `Invalid selection`.

The program now explains what went wrong and what the user should enter.

For example, non-numeric input displays:

`Invalid input. Please enter a number only.`

An out-of-range menu selection tells the user to choose a number within the valid range.

These changes make it easier for users to understand how to correct an invalid entry without guessing.

I also kept menu prompts and navigation consistent throughout the application so users can move between the main menu, Learning Path, Hands-On Labs, and training challenges without confusing transitions.

## Testing and Debugging

I tested the application throughout development by compiling and running the program after implementing new features.

Testing included:

- Main menu navigation
    
- Valid and invalid menu input
    
- Learning Path navigation
    
- Learning module prerequisite checks
    
- XP-based module unlocking
    
- Total XP and available XP tracking
    
- Challenge completion
    
- Hands-on lab navigation
    
- Terminal Investigation commands
    
- Lab objective completion
    
- Lab XP rewards
    
- Prevention of duplicate XP rewards
    
- Integration between Terminal Investigation and Computer Fundamentals
    

I also tested invalid input by entering text instead of a number and entering numbers outside the valid menu range.

The program successfully handled these inputs and displayed the improved error messages.

## Testing Evidence

The following screenshots were captured as evidence of Milestone 2 development and testing:

![Milestone 2 Program Run](https://chatgpt.com/images/milestone2-run.png)

![Milestone 2 Input Testing](https://chatgpt.com/images/milestone2-testing.png)

## What Changed and Why

The main goal of Milestone 2 was to move BugBountyTrainer beyond a basic challenge menu and create a more complete training application.

The Learning Path provides users with a clear progression system. The XP system gives the user a way to track progress and unlock additional content. Hands-on labs provide simulated practice instead of relying only on question-based challenges.

The usability improvements make the application easier to understand when incorrect input is entered.

The new class structure also makes the program easier to maintain because learning modules, challenges, researchers, and labs each have separate responsibilities.

## Current Status

BugBountyTrainer now has a functional main menu, researcher progression system, training challenges, progressive Learning Path, and simulated hands-on lab system.

Future development will focus on adding more complete training activities to the later learning modules, creating additional hands-on labs, and continuing to improve the progression system.