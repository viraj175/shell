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
        parse_command(cmd, out->args);
        cmd = strtok_r(NULL, "|", &savecmd);
        parse_command(cmd, out->pipe_args);
    }
    if (strchr(command, '>'))
    {
        out->has_redirection = 1;
        if (strstr(command, ">>")) out->flags = O_WRONLY | O_CREAT | O_APPEND;
        else out->flags = O_WRONLY | O_CREAT | O_TRUNC;
        cmd = strtok_r(command, ">", &savecmd);
        parse_command(cmd, out->args);
        cmd = strtok_r(NULL, ">", &savecmd);
        out->filename = trim(cmd);
    }
    if (!out->has_pipes && !out->has_redirection) 
        parse_command(command, out->args);
}

void
redirection(command_t *out)
{
    out->fd = open(out->filename, out->flags, 0644);
    if(out->fd == -1)
    {
        perror("ERROR");
        return;
    }
    dup2(out->fd, 1);
}

int
execute_command(command_t *out)
{
    if (out->has_pipes) pipe(out->fds);
    if (fork() == 0)
    {
        if (out->has_redirection) redirection(out);
        if (out->has_pipes)
        {
            close(out->fds[0]);
            dup2(out->fds[1], STDOUT_FILENO);
            close(out->fds[1]);
        }
        execvp(out->args[0], out->args);
        perror("exec failed!");
        exit(EXIT_FAILURE);
    }
    if (out->has_pipes && fork() == 0)
    {
        close(out->fds[1]);
        dup2(out->fds[0], STDIN_FILENO);
        close(out->fds[0]);
        execvp(out->pipe_args[0], out->pipe_args);
        perror("exec failed!");
        exit(EXIT_FAILURE);
    }

    if (out->has_pipes)
    {
        close(out->fds[0]);
        close(out->fds[1]);
    }

    wait(NULL);
    if (out->has_pipes) wait(NULL);
    return 0;
}

