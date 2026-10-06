# Version Control Reference

**Course Code:** COS1  
**Course Name:** Project and Portfolio I: Computer Science - Online  
**Student Name:** Raymond Smith  
**Due Date:** October 3, 2026  

This paper addresses some of the topic matter covered in research and activity this week. Reference links are included at the bottom for the research and information used to complete this assignment.

## Topic: Terminal

Professional developers use Terminal daily. It is important to understand basic commands because they make it possible to move through folders, inspect files, and work with Git without relying only on graphical tools.

### 1. Essential Terminal Commands

The examples below use common Bash/Git Bash/macOS/Linux command syntax.

- `clear`: Clear the screen
- `pwd`: Print the current working directory
- `ls`: List files and folders
- `ls -a`: List files and folders, including hidden files
- `ls -lah`: List all files and folders in a detailed, human-readable format
- `cd folderName`: Change directory to a specific folder
- `cd /`: Change directory to the root directory
- `cd ~`: Change directory to the user's home directory
- `cd ..`: Go up one folder level
- `cd ../..`: Go up two folder levels
- `cd ~/Desktop`: Change directory to the user's Desktop folder

### 2. Folder Drop

When I type `cd` followed by a space and drag a folder into the Terminal window, the full path to that folder is inserted automatically. After pressing Enter, Terminal changes the current working directory to that folder. I can use `pwd` afterward to confirm that I am now working inside the folder I dragged into Terminal.

## Topic: Version Control & Git

Version control records changes to files over time so developers can review previous versions, recover from mistakes, and work on projects in an organized way. Git is a distributed version control system and is the system I am using for my BugBountyTrainer project.

### 1. Three Types of Version Control

**Local Version Control:**  
A local version control system stores the file history on one computer. It is useful for tracking changes made by one person, but it does not provide the same collaboration features as systems designed to work across multiple computers.

**Centralized Version Control:**  
A centralized version control system stores the main project history on one central server. Developers connect to that server to get files and submit changes. This makes collaboration easier than local version control, but the central server can become a single point of failure.

**Distributed Version Control:**  
A distributed version control system gives each developer a complete copy of the repository and its history. Developers can work locally and later synchronize their changes with a remote repository. Git is a distributed version control system, which makes it useful for branching, collaboration, and working even when a network connection is unavailable.

### 2. Essential Git Commands

- `git clone https://github.com/USERNAME/REPOSITORY.git`: Clone a repository using HTTPS
- `git config --global user.name "Your Name"`: Set a global Git user name
- `git config --global user.email "your-email@example.com"`: Set a global Git email address
- `git status`: Show the current state of the working directory and staging area
- `git add .`: Stage current changes for the next commit
- `git commit -m "Commit message"`: Create a commit with a descriptive message
- `git log`: Show the commit history
- `git help`: Open Git's help system

For my current Git setup, I use my GitHub identity and verified school email so that my commits are attributed to the correct GitHub account.

### 3. Connecting to GitHub Using HTTPS

To connect to a GitHub repository using HTTPS, I first open the repository on GitHub and select **Code**, then choose **HTTPS** and copy the repository URL. In Terminal, I move to the folder where I want the repository and use `git clone` followed by the HTTPS URL.

For an existing local repository, I can connect it to GitHub with a command such as:

`git remote add origin https://github.com/USERNAME/REPOSITORY.git`

After the remote is connected, I can push my branch with a command such as:

`git push -u origin main`

or, if I am working on a development branch:

`git push -u origin dev`

GitHub no longer uses normal account passwords for command-line Git authentication. On my Windows computer, Git Credential Manager can handle the authentication process. A personal access token can also be used when Git requests HTTPS credentials.

### 4. Using .gitignore and Why It Is Important

**What is the purpose of this file?**  
A `.gitignore` file tells Git which files and folders should not be tracked or committed to the repository. This is useful for generated files, temporary files, IDE settings, build output, and other files that are not part of the project's source code. It helps keep the repository clean and prevents unnecessary machine-specific files from being shared.

**What is the `.DS_Store` file and why would you want to ignore it?**  
`.DS_Store` is a metadata file created by macOS Finder to store folder display information, such as icon positions and view settings. It is not part of a software project's source code, so it should usually be ignored. Committing it would add unnecessary operating-system-specific files to the repository.

**What other file or folder would you want to add to a .gitignore file and why?**  
For a Visual Studio C++ project, I would ignore folders such as `.vs/`, `x64/`, `Debug/`, and `Release/`. These folders contain local Visual Studio settings or compiled build output that can be recreated from the source code. Ignoring them keeps the repository smaller and focused on files that are actually needed to build and understand the project.

# Reference Links

**Research Summary:**  
The resources I found most helpful were the official Git documentation and GitHub documentation. The Pro Git book clearly explained the differences between local, centralized, and distributed version control, while the GitHub documentation was useful for learning HTTPS repository connections, cloning, and `.gitignore` files. These resources also connect directly to the Git commands I have been using while developing BugBountyTrainer.

**Terminal Commands**  
[Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)

**Three Types of Version Control**  
[Pro Git - About Version Control](https://git-scm.com/book/en/v2/Getting-Started-About-Version-Control)

**Git Commands**  
[Git Documentation](https://git-scm.com/docs)  
[Pro Git - First-Time Git Setup](https://git-scm.com/book/en/v2/Getting-Started-First-Time-Git-Setup)

**Connecting to GitHub using Terminal**  
[GitHub Docs - Cloning a Repository](https://docs.github.com/en/repositories/creating-and-managing-repositories/cloning-a-repository)  
[GitHub Docs - About Remote Repositories](https://docs.github.com/en/get-started/git-basics/about-remote-repositories)

**Using .gitignore and Why It's Important**  
[GitHub Docs - Ignoring Files](https://docs.github.com/en/get-started/git-basics/ignoring-files)  
[GitHub gitignore - macOS Template](https://github.com/github/gitignore/blob/main/Global/macOS.gitignore)
