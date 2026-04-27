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

#endif // !SHELL_H
