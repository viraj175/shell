#include "shell.h"
#include <unistd.h>

int
main ()
{
    char command[COMMAND_SIZE];

    while (1)
    {
        printf("> ");
        fgets(command, COMMAND_SIZE, stdin);
        command[strcspn(command, "\n")] = '\0';
        char *args[100];
        parse_command(args, command);
        if (strcmp(args[0], "cd") == 0) 
        {
            chdir(args[1]);
            continue;
        }
        if(strcmp(command, "exit") == 0) exit(0);
        execute_command(args);

    }
    return 0;
}
