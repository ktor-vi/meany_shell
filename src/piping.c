#include "../includes/minishell.h"

#define MAX_ARGC 3

int main(void) {
    char **commands = malloc(sizeof(char *) * 3);
    commands[0] = "ls";
    commands[1] = "-l";
    commands[2] =  NULL;
        // {"wc", "-l", NULL},
        // {"xargs", "printf", "0x%x\n", NULL},
        // {"cowsay", NULL}

    t_entry *envp = malloc(sizeof(t_entry));
    envp->name = "PATH";
    envp->value = getenv("PATH");
    envp->next = NULL;
    size_t i, n;
    int prev_pipe, pfds[2];
    printf("%s\n", get_cmdpath(commands, envp));
    n = sizeof(commands) / sizeof(*commands);
    prev_pipe = STDIN_FILENO;

    for (i = 0; i < n - 1; i++) {
        pipe(pfds);

        if (fork() == 0) {
            // Redirect previous pipe to stdin
            if (prev_pipe != STDIN_FILENO) {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            // Redirect stdout to current pipe
            dup2(pfds[1], STDOUT_FILENO);
            close(pfds[1]);

            // Start command
            execve(get_cmdpath(commands, envp), commands, NULL);

            perror("execvp failed");
            exit(1);
        }

        // Close read end of previous pipe (not needed in the parent)
        close(prev_pipe);

        // Close write end of current pipe (not needed in the parent)
        close(pfds[1]);

        // Save read end of current pipe to use in next iteration
        prev_pipe = pfds[0];
    }

    // Get stdin from last pipe
    if (prev_pipe != STDIN_FILENO) {
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }

    // Start last command
    execve(get_cmdpath(commands, envp), commands, NULL);

    perror("execvp failed");
    exit(1);
}
