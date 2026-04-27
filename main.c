#include "shell.h"

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
        if(strcmp(command, "exit") == 0) exit(0);

        pid_t pid = fork();
        if (pid == 0)
        {
            execvp(command , args);
            perror("exec failed!");
            return 1;
        }
        else wait(NULL);
    }
    return 0;
}
