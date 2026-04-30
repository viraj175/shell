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
typedef unsigned char u8 ;

typedef struct command
{
    char *filename;
    char *args[ARG_SIZE];
    char *pipe_args[ARG_SIZE];
    int fds[2];
    int fd;
    int flags;
    int has_pipes;
    int has_redirection;
} 
command_t;

// Function definition
void parse_command(char *command, char *args[]);
void handle_command(char *command, command_t *out);
void pipe_arguments(char *command, command_t *out);
void redirection(command_t *out);
int execute_command(command_t *out);
char *trim(char *str);

#endif // !SHELL_H
