#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include "command.h"

void listDir() {
    DIR *dir = opendir(".");
    if (dir == NULL) {
        write(STDOUT_FILENO, "Error: Failed to open current directory\n", 40);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        write(STDOUT_FILENO, entry->d_name, strlen(entry->d_name));
        write(STDOUT_FILENO, " ", 1);
    }
    write(STDOUT_FILENO, "\n", 1);

    closedir(dir);
}

void showCurrentDir() {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        write(STDOUT_FILENO, cwd, strlen(cwd));
        write(STDOUT_FILENO, "\n", 1);
    } else {
        write(STDOUT_FILENO, "Error: Failed to get current directory\n", 39);
    }
}

void makeDir(char *dirName) {
    if (mkdir(dirName, 0755) == -1) {
        write(STDOUT_FILENO, "Error: Failed to create directory\n", 34);
    }
}

void changeDir(char *dirName) {
    if (chdir(dirName) == -1) {
        write(STDOUT_FILENO, "Error: Failed to change directory\n", 34);
    }
}

void copyFile(char *sourcePath, char *destinationPath) {
    int srcFd = open(sourcePath, O_RDONLY);
    if (srcFd < 0) {
        write(STDOUT_FILENO, "Error: Cannot open source file\n", 32);
        return;
    }

    struct stat st;
    char fullDestPath[1024];
    int dstFd;

    if (stat(destinationPath, &st) == 0 && S_ISDIR(st.st_mode)) {
        const char *filename = strrchr(sourcePath, '/');
        filename = (filename != NULL) ? filename + 1 : sourcePath;
        snprintf(fullDestPath, sizeof(fullDestPath), "%s/%s", destinationPath, filename);
        dstFd = open(fullDestPath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    } else {
        dstFd = open(destinationPath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    if (dstFd < 0) {
        write(STDOUT_FILENO, "Error: Cannot open destination file\n", 36);
        close(srcFd);
        return;
    }

    char buffer[1024];
    ssize_t bytesRead, bytesWritten;
    while ((bytesRead = read(srcFd, buffer, sizeof(buffer))) > 0) {
        bytesWritten = write(dstFd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            write(STDOUT_FILENO, "Error: Write failure\n", 22);
            break;
        }
    }

    close(srcFd);
    close(dstFd);
}

void moveFile(char *sourcePath, char *destinationPath) {
    int srcFd = open(sourcePath, O_RDONLY);
    if (srcFd < 0) {
        write(STDOUT_FILENO, "Error: Cannot open source file\n", 32);
        return;
    }

    struct stat st;
    char fullDestPath[1024];
    int dstFd;

    if (stat(destinationPath, &st) == 0 && S_ISDIR(st.st_mode)) {
        const char *filename = strrchr(sourcePath, '/');
        filename = (filename != NULL) ? filename + 1 : sourcePath;
        snprintf(fullDestPath, sizeof(fullDestPath), "%s/%s", destinationPath, filename);
        dstFd = open(fullDestPath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    } else {
        dstFd = open(destinationPath, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    }

    if (dstFd < 0) {
        write(STDOUT_FILENO, "Error: Cannot open destination file\n", 36);
        close(srcFd);
        return;
    }

    char buffer[1024];
    ssize_t bytesRead, bytesWritten;
    while ((bytesRead = read(srcFd, buffer, sizeof(buffer))) > 0) {
        bytesWritten = write(dstFd, buffer, bytesRead);
        if (bytesWritten != bytesRead) {
            write(STDOUT_FILENO, "Error: Write failure\n", 22);
            break;
        }
    }

    close(srcFd);
    close(dstFd);

    if (unlink(sourcePath) == -1) {
        write(STDOUT_FILENO, "Error: Failed to delete original file\n", 38);
    }
}

void deleteFile(char *filename) {
    if (unlink(filename) == -1) {
        write(STDOUT_FILENO, "Error: Failed to delete file\n", 30);
    }
}

void displayFile(char *filename) {
    int fd = open(filename, O_RDONLY);
    if (fd < 0) {
        write(STDOUT_FILENO, "Error: Cannot open file\n", 25);
        return;
    }

    char buffer[1024];
    ssize_t bytesRead;
    while ((bytesRead = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytesRead);
    }

    close(fd);
}
