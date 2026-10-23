\# BugBountyTrainer — Milestone 4



\*\*Project:\*\* BugBountyTrainer

\*\*Course:\*\* Project and Portfolio I: Computer Science

\*\*Milestone:\*\* 4 — Final Development

\*\*Development Language:\*\* C++20

\*\*Development Environment:\*\* Visual Studio 2022



\## 1. Project Overview



BugBountyTrainer is a C++ console application designed to introduce users to ethical hacking, cybersecurity fundamentals, and bug bounty concepts through interactive training.



The application provides structured learning modules, cybersecurity assessments, hands-on exercises, researcher profiles, and an XP-based progression system.



During Milestone 4, development focused on improving application stability, expanding researcher functionality, refactoring existing code, and strengthening progress persistence.



\## 2. Final Features Added



\### Researcher Statistics



Added a Researcher Statistics screen that displays important information about the user's training progress.



This includes:



\* Researcher name and level

\* Total XP earned

\* Available XP

\* Total training challenges

\* Completed challenges

\* Remaining challenges



This feature provides researchers with a clearer understanding of their progress.



\### Tool Inventory and Tool Shop



Implemented a Tool class and an Inventory class to support XP-based tool purchases.



Researchers can purchase simulated training tools, including Nmap, Wireshark, Burp Suite, and SQLmap.



The inventory system prevents duplicate purchases and uses available XP without reducing lifetime XP.



\### Inventory Persistence



Extended the save system to support purchased tools.



The new V7 save format records researcher inventory alongside existing progression information.



Purchased tools can be restored without charging XP again.



\## 3. Refactoring and Maintainability Improvements



\### LearningPathManager



Extracted Learning Path functionality from TrainerApp into a dedicated LearningPathManager.



This improves separation of responsibilities and reduces the amount of learning-related logic handled directly by the main application class.



\### SavedUserManager



Separated saved-user discovery, filename generation, and profile labeling into a dedicated class.



SaveManager remains responsible for serializing and restoring researcher progress.



\### Inventory and Researcher Organization



Introduced separate Tool and Inventory classes.



The Researcher class manages purchases and XP transactions, while Inventory manages ownership and prevents duplicate tools.



\### Menu Navigation



Improved menu pause handling to reduce inconsistent navigation behavior.



The application also uses validated numeric input to reject invalid menu selections.



\## 4. Bug Fixes



\### Save-File Compatibility



Updated save-file detection to recognize the V7 format while retaining support for older save versions.



This resolved a problem where valid V7 researcher profiles were not appearing in the saved-user selection menu.



\### Inventory Purchasing



Verified that purchased tools are added to the researcher's inventory and duplicate purchases are prevented.



\### SQL Academy Menu Integration



Corrected the main menu switch structure to preserve SQL Academy functionality, including lesson completion tracking and XP rewards.



\### Compilation and Linker Issues



Resolved duplicate function definitions and misplaced function implementations during inventory integration.



Rebuilt the project successfully after correcting these issues.



\## 5. Usability Improvements



The final application includes:



\* A structured main menu

\* Researcher statistics

\* Clear Tool Shop purchase messages

\* Inventory ownership indicators

\* Input validation

\* Save and load options

\* Navigation prompts

\* Training completion feedback

\* XP progression information



These improvements make the application easier to navigate and understand.



\## 6. Testing and Validation



Testing performed during development included:



\* Successful Visual Studio compilation

\* Tool purchasing

\* Available XP deduction

\* Duplicate purchase prevention

\* Inventory display

\* V7 save-file recognition

\* Saving and reloading purchased tools

\* Restoration of saved researcher information



Additional final regression testing should verify all major menu options, invalid input handling, application exit behavior, and interactions among existing training systems.



\## 7. Instructor Feedback and Future Improvements



Instructor and peer feedback emphasized modular design, maintainability, extensibility, and reliable progress persistence.



The project has incorporated modular components and versioned save files.



Future improvements may include:



\* Interfaces and polymorphism for training modules

\* A centralized module registry

\* JSON-based lesson definitions

\* Transactional save-file writing

\* Checksums for detecting corrupted save data

\* Unique reward identifiers

\* SQLite persistence

\* Additional isolated cybersecurity training labs

\* Windows desktop and web-based interfaces



These features are planned for future development rather than the final Milestone 4 submission.



\## 8. Conclusion



Milestone 4 represents the final development and stabilization phase of BugBountyTrainer for Project and Portfolio I.



The application has progressed from a basic cybersecurity training console program into a more structured learning system with researcher progression, interactive training, tool purchases, inventory management, and persistent save data.



The final milestone emphasizes maintainability, reliability, usability, documentation, and preparation for future development.



