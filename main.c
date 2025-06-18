#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "command.h"
#include "string_parser.h"

#define MAX_ARGS 3

int execute_command(command_line *cmd, FILE *output) {
    if (cmd == NULL || cmd->command_list == NULL || cmd->num_token == 0) return -1;

    char **args = cmd->command_list;
    int argc = cmd->num_token;

    if (strcmp(args[0], "ls") == 0 && argc == 1) {
        listDir();
    } else if (strcmp(args[0], "pwd") == 0 && argc == 1) {
        showCurrentDir();
    } else if (strcmp(args[0], "mkdir") == 0 && argc == 2) {
        makeDir(args[1]);
    } else if (strcmp(args[0], "cd") == 0 && argc == 2) {
        changeDir(args[1]);
    } else if (strcmp(args[0], "cp") == 0 && argc == 3) {
        copyFile(args[1], args[2]);
    } else if (strcmp(args[0], "mv") == 0 && argc == 3) {
        moveFile(args[1], args[2]);
    } else if (strcmp(args[0], "rm") == 0 && argc == 2) {
        deleteFile(args[1]);
    } else if (strcmp(args[0], "cat") == 0 && argc == 2) {
        displayFile(args[1]);
    } else if (strcmp(args[0], "exit") == 0) {
        exit(0);
    } else {
        fprintf(output, "Error in command: %s - Invalid command or wrong number of arguments\n", args[0]);
        return -1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    FILE *input = stdin;
    FILE *output = stdout;
    int file_mode = 0;

    if (argc == 3 && strcmp(argv[1], "-f") == 0) {
        file_mode = 1;
        input = fopen(argv[2], "r");
        output = fopen("output.txt", "w");
        if (!input || !output) {
            fprintf(stderr, "Error: Cannot open input or output file.\n");
            return 1;
        }
        dup2(fileno(output), STDOUT_FILENO); 
    } else if (argc != 1) {
        fprintf(stderr, "Usage: %s OR %s -f <filename>\n", argv[0], argv[0]);
        return 1;
    }

    char *line = NULL;
    size_t len = 0;

    while (1) {
        if (!file_mode) fprintf(stdout, ">>> ");
        ssize_t read = getline(&line, &len, input);
        if (read == -1) break;

        line[strcspn(line, "\n")] = '\0';

        char *token = strtok(line, ";");
        while (token) {
            while (*token == ' ') token++;  
            if (*token == '\0') {
                token = strtok(NULL, ";");
                continue;
            }

            if (file_mode) {
                fprintf(output, ">>> %s\n", token);
            }

            command_line cmd = str_filler(token, " ");
            (void) execute_command(&cmd, output);
            free_command_line(&cmd);

            fprintf(output, "\n"); 

           
            token = strtok(NULL, ";");
        }
    }

    free(line);
    if (file_mode) {
        fclose(input);
        fclose(output);
    }

    return 0;
}



