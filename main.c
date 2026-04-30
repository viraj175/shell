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
        command_t fill;
        printf("> ");
        fgets(command, COMMAND_SIZE, stdin);
        command[strcspn(command, "\n")] = '\0';
        handle_command(command, &fill);

        if (strcmp(fill.args[0], "cd") == 0) 
        {
            chdir(fill.args[1]);
            continue;
        }

        if(strcmp(command, "exit") == 0) exit(0);

        execute_command(&fill);
        if(fill.has_redirection) close(fill.fd);
    }
    return 0;
}
