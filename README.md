# PseudoShellC
A simple Unix-style shell implementation in C that supports basic commands like ls, pwd, mkdir, cd, cp, mv, rm, and cat. The shell works in both interactive mode and file mode, where a set of commands can be read and executed from a .txt file.

Features:
Interactive mode: Type commands directly into the terminal.
File mode: Execute commands from a .txt file.

Support for common Unix commands:

ls: List files in the current directory.
pwd: Print the current working directory.
mkdir <dir_name>: Create a new directory.
cd <dir_name>: Change the current directory.
cp <src> <dest>: Copy files.
mv <src> <dest>: Move files.
rm <file>: Remove a file.
cat <file>: Display file contents.

Error handling: Handles invalid input, missing arguments, and command execution failures.

System calls: Utilizes system calls like fork(), exec(), chdir(), getcwd(), open(), and more for process control and file system interaction.

Installation:
Prerequisites
A Linux or Unix-like environment (macOS, WSL, etc.)

GCC compiler

Steps to Compile and Run:
Clone the repository:
git clone https://github.com/yourusername/pseudo-shell-in-c.git
cd pseudo-shell-in-c

Compile code:
gcc main.c command.c string_parser.c -o shell

Run Shell:
./shell

Run with .txt file:
./shell < commands.txt

Usage:
Interactive Mode:
Once the shell is running, you can type commands directly into the terminal. The shell will execute the commands and display the results. Supported commands include:

ls: List files in the current directory.
pwd: Display the current working directory.
mkdir <dir_name>: Create a new directory.
cd <dir_name>: Change the current directory.
cp <src> <dest>: Copy a file from src to dest.
mv <src> <dest>: Move a file from src to dest.
rm <file>: Remove the specified file.
cat <file>: Display the contents of the file.

File Mode:
In file mode, the shell will read commands from a .txt file and execute them. This is useful for automating tasks or running a batch of commands.

Example command file (commands.txt):

mkdir test_dir
cd test_dir
touch newfile.txt
cat newfile.txt
Run the shell with the file:

Run with .txt file:
./shell < commands.txt

Performance Results

Memory Usage:
The program was tested with Valgrind to ensure there were no memory leaks. All memory operations were validated successfully with no leaks detected.

Issues with Test Script:
While the shell passed the functionality tests, the output formatting didn’t match the exact specifications expected by the provided test script:
cat command: The shell printed the command prompt before executing the cat command, which caused the test to fail.
Output Formatting: The output sequence and positioning of prompts were different from what the test script expected. However, the output was still clear, and the commands worked as described in the project requirements.
