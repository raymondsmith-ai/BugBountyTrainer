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
* SQL Fundamentals lessons, guided practice, and assessment
* SQL Injection Stage 2 training
* SQL Academy with 13 progressive learning modules
* SQL Academy assessments and completion tracking
* One-time XP rewards for completed SQL training
* Docker-based SQL Injection training labs
* SaveManager V6 persistent save/load system
* Researcher progress restoration
* SQL Academy completion persistence
* Corrupted save-file validation
* Saved-user profile selection
* Automated regression testing
* 52 successful regression checks with zero failures
* Improved main menu pause handling

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

## Week 3 / Milestone 3

Completed:

* Implemented SQL Fundamentals training
* Added guided SQL practice and assessments
* Developed SQL Injection Stage 2 training
* Expanded Docker-based training labs
* Introduced SQL Academy with 13 modules
* Integrated training completion with XP progression
* Improved save/load functionality
* Added additional progress tracking
* Continued application testing and debugging

## Week 4 / Milestone 4

Completed:

* Updated SaveManager to V6
* Integrated SQL Academy completion persistence
* Improved corrupted save-file detection
* Improved saved-user filename validation
* Resolved duplicate saved-user entries caused by backup files
* Refactored main menu pause handling
* Updated regression tests for the current SaveManager interface
* Successfully completed 52 regression checks with zero failures
* Tested researcher profile loading and menu navigation
* Updated final project documentation
* Prepared final project submission materials

## Future Development

* Continue refactoring TrainerApp into smaller components
* Expand automated regression testing
* Develop additional interactive cybersecurity labs
* Improve Docker-based training environments
* Explore Windows desktop and web application versions
* Research AI-assisted cybersecurity tutoring
## Technologies

* C++20
* Microsoft Visual Studio
* Git
* GitHub
* GitHub Projects
* PowerShell
* Docker
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
## Week 3 – Project Stand-Up

### Overview
This week, I focused on expanding BugBountyTrainer and improving its stability.

### Improvements
I added SQL Fundamentals lessons, guided practice, and an assessment. I also improved progress saving and implemented one-time XP rewards.

### Challenges
Integrating new features with the save/load system was challenging. I worked through these issues by testing functionality and fixing progress-tracking problems.

### Feedback
Previous feedback encouraged better input validation, progression, and code organization. I've continued improving these areas.

### Next Steps
For Week 4, I'll focus on testing, refactoring, and preparing the final milestone while planning future cybersecurity labs.

## Final Project Stand-Up — Week 4 / Milestone 4

### Project Overview

Throughout Project & Portfolio I, I developed BugBountyTrainer from a basic C++ console application into a more comprehensive cybersecurity training program.

The application introduces users to ethical hacking and bug bounty concepts through interactive challenges, structured learning modules, simulated hands-on labs, and SQL training exercises.

Users can create researcher profiles, earn XP, increase their levels, unlock learning modules, complete training activities, and save their progress.

### Accomplishments

One of my biggest accomplishments was successfully integrating multiple systems into one working application.

During the course, I implemented researcher progression, training challenges, vulnerability categories, a progressive learning path, and hands-on labs.

I also expanded the application with SQL Fundamentals, SQL Injection training, and SQL Academy, which contains 13 learning modules.

Another major accomplishment was implementing the V6 save/load system. This allows the application to preserve researcher progress, training completion, and SQL Academy results between sessions.

During Week 4, I improved error handling, corrected saved-user discovery issues, and refactored menu navigation to improve maintainability.

I also updated the automated regression tests after receiving instructor feedback. The final test run successfully completed 52 checks with zero failures.

### Challenges and Problem-Solving

One challenge was managing the growing complexity of TrainerApp.cpp as new features were introduced.

I began addressing this by separating menu pause-handling logic into a dedicated helper function.

Another challenge involved maintaining compatibility between SaveManager and the automated regression tests. As the save system expanded, the older tests no longer matched the updated function signatures.

I corrected the test configuration, updated the SaveManager calls, resolved compilation errors, and successfully executed the regression tests.

I also encountered problems involving save-file validation and duplicate saved-user entries. These issues taught me the importance of validating persistent data and organizing backup files properly.

### Lessons Learned

This project strengthened my understanding of object-oriented programming, C++ class design, debugging, file management, and software testing.

I also gained valuable experience using Git and GitHub for version control, development planning, and tracking project progress.

One important lesson was that software development involves more than implementing features. Reliable applications require testing, code maintenance, clear documentation, and continuous improvement.

I learned to approach problems systematically, make smaller changes, and verify functionality before continuing development.

### Future Development

After completing this course, I plan to continue improving BugBountyTrainer.

My future goals include refactoring larger components into smaller classes, expanding interactive cybersecurity labs, improving automated testing, and developing more advanced training content.

Eventually, I would like to explore transforming BugBountyTrainer into a Windows desktop application and web-based cybersecurity training platform.

I am also interested in incorporating AI-assisted tutoring to provide personalized explanations and educational guidance.

### Final Reflection

BugBountyTrainer has been one of my most significant programming projects so far.

I started this course with an idea and gradually transformed it into a functional C++ application with multiple interconnected systems.

Throughout the development process, I improved my programming skills, gained confidence in debugging, and developed a better understanding of professional software development workflows.

I am proud of the progress I made and plan to continue developing the project beyond this course.


## Author

Raymond Smith
