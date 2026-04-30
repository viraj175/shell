#include "shell.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

char*
trim(char *str)
{
    while(isspace(*str)) str++;
    char *end = str + strlen(str) - 1;
    while(isspace(*end)) end--;
    *(end + 1) = '\0';
    return str;
}

void
parse_command(char *command, char *args[])
{
    char *saveptr;
    char *token = strtok_r(command, " ", &saveptr);
    u8 i = 0;
    args[i] = token;

    while (token)
    {
        token = strtok_r(NULL, " ", &saveptr);
        args[++i] = token;
    }
    args[++i] = NULL;
}

void 
handle_command(char *command, command_t *out)
{
    out->has_pipes = 0;
    out->has_redirection = 0;
    char *savecmd, *cmd;
    if (strchr(command, '|'))
    {
        out->has_pipes = 1;
        cmd = strtok_r(command, "|", &savecmd);
        parse_command(cmd, out->pipe_args);
        cmd = strtok_r(NULL, "|", &savecmd);
        parse_command(cmd, out->args);
    }
    if (strchr(command, '>'))
    {
        out->has_redirection = 1;
        cmd = strtok_r(command, ">", &savecmd);
        parse_command(cmd, out->args);
        cmd = strtok_r(NULL, ">", &savecmd);
        out->filename = trim(cmd);
    }
    if (!out->has_pipes && !out->has_redirection) 
        parse_command(command, out->args);
}

int
execute_command(command_t *out)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        execvp(out->args[0], out->args);
        perror("exec failed!");
        return -1;
    }
    else 
    {
        wait(NULL);
    }
    return 0;
}

