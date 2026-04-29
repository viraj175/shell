#include "shell.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int
main ()
{
    char command[COMMAND_SIZE];

    while (1)
    {
        FileInfo file;
        *(file.outfile) = NULL;
        printf("> ");
        fgets(command, COMMAND_SIZE, stdin);
        command[strcspn(command, "\n")] = '\0';
        char *args[ARG_SIZE];
        parse_command(args, command, &file);
        if (strcmp(args[0], "cd") == 0) 
        {
            chdir(args[1]);
            continue;
        }
        if(strcmp(command, "exit") == 0) exit(0);
        execute_command(args, file);
        close(file.fd);
    }
    return 0;
}
