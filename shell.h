#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define COMMAND_SIZE 100
#define ARG_SIZE 30
#define FILE_NAME 20

typedef struct fileinfo 
{
    char *outfile[FILE_NAME];
    int fd;
    int flags;
} FileInfo;

// Function definition
void parse_command(char *args[], char *command, FileInfo *file);
char *search(const char *command, const char find);
void execute_command(char *args[], FileInfo file);
void redirection(FileInfo *file);
char *trim(char *str);

#endif // !SHELL_H
