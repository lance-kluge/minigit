# CSCI 2275 – Data Structures - Final Project

Created by: Lance Kluge and Ephram Cukier

This program attempts to create a file version control system by which you have saved versions or checkpoints of many files. This is a similar, yet less advanced version of git.

Basic Functionality of the program starts when you cd into the build directory of the project and run "cmake .." Then you should run the command "make". To then start the application, run "./run_app_1" and the program starts.

This brings up a text based menu giving you 7 options. 

1. Init: This must be done before you can run the add, rm, commit, checkout, and search commands. It initializes the underlying data structures.

2. Add: This should only be run when you have a valid path that you want tracked. The program will prompt you for a file to add to the version control and if you input an invalid file path it will continue to prompt you for a file that exists until it receives one. If you input a file that has already been added, the program will accept that, but realize that it has already been added and not make a duplicate add of this file.

3. Rm: The rm command is used for if the user wants to remove a file that is currently being tracked. If you input a file that is not currently being tracked, the program will still accept the command as it guarantees that the file is no longer being tracked. Note: if you add a file, commit at least once with that file being tracked, remove that file and then decide that you would like to add that file back, the program will pick up where it left off with the version numbers.

4. Commit: When you would like to make a hard checkpoint of the file versions that you are tracking you should use the commit option. If the program detects that there have been no changes to any files that you are tracking, it will not allow a commit. However if it detects that there are in fact changes that have been made it will prompt you for a commit message. Once it has the commit message it will snapshot the files being tracked and store them with a tie to the commit message and number.

5. Checkout: If you would like to look at the previous versions of files, you can use the checkout call. WARNING: This will erase any uncommitted changes you have made to any files and the program will tell you as such. Once you have gotten past the warning the program will prompt you for what commit number you would like to checkout. Once you enter a valid commit number, the program will restore every file that was included in that commit number to its version consistent with its commit. When you have checked out any commit that is not the most recent, you may not add, remove, or commit anything. When you have finished checkout the most recent commit and you may continue adding, committing, and removing.

6. Search: The search command with prompt you for a singular word to search the commit messages for. It will then print out the numbers of the commit messages that contain that word, or if no commit messages contain that word it will tell you that there are no commit messages that contain the inputed word.

7. Quit: When you would like to terminate the program, enter 7 to quit. This will deconstruct the program, insuring no memory leaks.
 
