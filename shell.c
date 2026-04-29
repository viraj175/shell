#include "shell.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void
parse_command(char *args[], char *command, FileInfo *file)
{
    char *saveptr;
    if(strstr(command, ">>"))
    {
        command = strtok_r(command, ">", &saveptr);
        *(file->outfile) = trim(strtok_r(NULL, ">", &saveptr));
        file->flags = O_WRONLY | O_CREAT | O_APPEND;
    }
    else if(search(command, '>'))
    {
        command = strtok_r(command, ">", &saveptr);
        *(file->outfile) = trim(strtok_r(NULL, ">", &saveptr));
        file->flags = O_WRONLY | O_CREAT | O_TRUNC;
    }
    else *(file->outfile) = NULL;

    // printf("filename: %s\n", *(file.outfile));
    char *token = strtok_r(command, " ", &saveptr);
    unsigned char i = 0;
    args[i] = token;
    while (token)
    {
        token = strtok_r(NULL, " ", &saveptr);
        args[++i] = token;
    }
}

char *
search(const char *command, const char find)
{
    return strchr(command, find);
}

char*
trim(char *str)
{
    char *end;
    while(isspace(*str)) str++;
    if(*str == '\0') return str;
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--; 
    return str;
}

void
redirection(FileInfo *file)
{
    // printf("outfile: %s\n", filename);
    file->fd = open(*(file->outfile), file->flags, 0644);

    if (file->fd == -1)
    {
        perror("Faild to open file!");
        return;
    }
    printf("file->fd: %d\n", file->fd);
    dup2(file->fd, 1);
}

void 
execute_command(char *args[], FileInfo file)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        // printf("arg[0]: %s\n", args[0]);
        if (*(file.outfile)) {printf("redirection!\n"); redirection(&file); } 
        execvp(args[0], args);
        perror("exec failed!");
        exit(1);
    }
    else {
        wait(NULL);
        // printf("parent exit!\n");
    }
}

