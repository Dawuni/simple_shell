0x16. C - Simple Shell
C Group project Syscall

Learning Objectives

At the end of this project, you are expected to be able to explain to anyone, without the help of Google:
General

    Who designed and implemented the original Unix operating system
    Who wrote the first version of the UNIX shell
    Who invented the B programming language (the direct predecessor to the C programming language)
    Who is Ken Thompson
    How does a shell work
    What is a pid and a ppid
    How to manipulate the environment of the current process
    What is the difference between a function and a system call
    How to create processes
    What are the three prototypes of main
    How does the shell use the PATH to find the programs
    How to execute another program with the execve system call
    How to suspend the execution of a process until one of its children terminates
    What is EOF / “end-of-file”?

1. Write a beautiful code that passes the Betty checks

2. Write a UNIX command line interpreter.

3. Simple shell 0.1 +
    Handle command lines with arguments

4. Simple shell 0.2 +

    Handle the PATH
    fork must not be called if the command doesn’t exist

5. Simple shell 0.3 +

    Implement the exit built-in, that exits the shell
    Usage: exit
    You don’t have to handle any argument to the built-in exit

6. Simple shell 0.4 +

    Implement the env built-in, that prints the current environment

7. Simple shell 0.1 +

    Write your own getline function
    Use a buffer to read many chars at once and call the least possible the read system call
    You will need to use static variables
    You are not allowed to use getline

You don’t have to:

    be able to move the cursor

8. Simple shell 0.2 +

    You are not allowed to use strtok

9. Simple shell 0.4 +

    handle arguments for the built-in exit
    Usage: exit status, where status is an integer used to exit the shell

10. Simple shell 1.0 +

Implement the setenv and unsetenv builtin commands

    setenv
        Initialize a new environment variable, or modify an existing one
        Command syntax: setenv VARIABLE VALUE
        Should print something on stderr on failure
    unsetenv
        Remove an environment variable
        Command syntax: unsetenv VARIABLE
        Should print something on stderr on failure

11. Simple shell 1.0 +

Implement the builtin command cd:

    Changes the current directory of the process.
    Command syntax: cd [DIRECTORY]
    If no argument is given to cd the command must be interpreted like cd $HOME
    You have to handle the command cd -
    You have to update the environment variable PWD when you change directory

man chdir, man getcwd

12. Simple shell 1.0 +

    Handle the commands separator ;
13. Simple shell 1.0 +

    Handle the && and || shell logical operators

14. Simple shell 1.0 +

    Implement the alias builtin command
    Usage: alias [name[='value'] ...]
        alias: Prints a list of all aliases, one per line, in the form name='value'
        alias name [name2 ...]: Prints the aliases name, name2, etc 1 per line, in the form name='value'
        alias name='value' [...]: Defines an alias for each name whose value is given. If name is already an alias, replaces its value with value

15. Simple shell 1.0 +

    Handle variables replacement
    Handle the $? variable
    Handle the $$ variable

16. Simple shell 1.0 +

    Handle comments (#)

17. Simple shell 1.0 +

    Usage: simple_shell [filename]
    Your shell can take a file as a command line argument
    The file contains all the commands that your shell should run before exiting
    The file should contain one command per line
    In this mode, the shell should not print a prompt and should not read from stdin

