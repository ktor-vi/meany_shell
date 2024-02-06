/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 06:51:50 by vphilipp          #+#    #+#             */
/*   Updated: 2024/02/05 06:51:51 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_pipes(t_minishell *minishell, t_entry *envp)
{
    t_command *h = minishell->cmd;
    int prev_pipe = STDIN_FILENO;
    int pfds[2];

    while (h->to_pipe == true)
    {
        pipe(pfds);
        pid_t child_pid = fork();

        if (child_pid == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0)
        {
            // Child process
            if (prev_pipe != STDIN_FILENO)
            {
                dup2(prev_pipe, STDIN_FILENO);
                close(prev_pipe);
            }

            dup2(pfds[1], STDOUT_FILENO);
            close(pfds[0]);
            close(pfds[1]);

            execve(h->path, h->args, ll_to_tab(envp));
            perror("execve failed");
            exit(EXIT_FAILURE);
        }
        else
        {
            // Parent process
            close(prev_pipe);
            close(pfds[1]);
            prev_pipe = pfds[0];
            h = h->next;
        }
    }

    // Parent process: close the last pipe
    close(prev_pipe);
    // Wait for all child processes to finish
    while (waitpid(-1, NULL, 0) != -1)
    {
        // Handle child process termination status if needed
    }

    // Execute the last command after the loop
    if (prev_pipe != STDIN_FILENO)
    {
        dup2(prev_pipe, STDIN_FILENO);
        close(prev_pipe);
    }

    execve(h->path, h->args, ll_to_tab(envp));
    perror("execve failed");
    exit(EXIT_FAILURE);
}
