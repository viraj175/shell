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

        if(fill.has_pipes)
        {
            u8 i = 0;
            while (fill.pipe_args[i])
            {
                printf("%s\t", fill.pipe_args[i++]);
            }
            printf("\n");
        }

        if(fill.has_redirection)
        {
            printf("filename: %s\n", fill.filename);
        }

        u8 i = 0;
        while (fill.args[i])
        {
            printf("%s\t", fill.args[i++]);
        }
        printf("\n");
        // execute_command(fill.args, &fill);
    }
    return 0;
}
