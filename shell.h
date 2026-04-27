#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define COMMAND_SIZE 100

// Function definition
void parse_command(char *args[], char *command);
void execute_command(char *args[]);

#endif // !SHELL_H
