#include "shell.h"

void
parse_command(char *args[], char *command)
{
    char *saveptr;
    unsigned char i = 0;
    char *token = strtok_r(command, " ", &saveptr);
    args[i] = token;
    while (token)
    {
        token = strtok_r(NULL, " ", &saveptr);
        args[++i] = token;
    }
}

void 
execute_command(char *args[])
{
    pid_t pid = fork();
    if (pid == 0)
    {
        execvp(args[0] , args);
        perror("exec failed!");
        exit(1);
    }
    else wait(NULL);
}

