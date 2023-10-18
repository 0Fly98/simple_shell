# simple_shell
This simple shell project is made in teams of two, open AUTHORS file for more information.

This program reads user input using getline function (stdin).
It  tokenizes the input string using strtok and strtow3.
It manouvers through directories to access built in functions and find executable files.
It executes commands using the wait process and fork function.
This shell will be compiled using gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

# What this shell achieves
Task 0: Writes a code that passes Betty checks
Task 1: Uses UNIX command line interpreter
Task 2: Handles command lines with arguments
Task 3: Handles the PATH where fork must not be called if the command doesnt exist
Task 4: Implement the exit built-in, that exits the shell
Task 5: Implement the env built-in, that prints the current environment
Task 6: Write getline function that uses buffer to read many chars at once and call the least possible the read system call
Task 7: Doesnt use strtok function to separate strings from delimeters
Task 8: handle arguments for the built-in exit
Task 9: Implements the setenv and unsetenv builtin commands
Task 10: Implements the builtin command cd
Task 11: Handles the commands separator ;
Task 12: Handles the && and || shell logical operators
Task 13: Implement the alias builtin command
Task 14: Handle variables replacement
Task 15: Handles comments (#)
Task 16: In this mode, the shell should not print a prompt and should not read from stdin
