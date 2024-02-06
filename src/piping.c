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
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	execute_pipes(t_minishell *minishell, t_entry *envp)
{
	t_command	*h;
	int			prev_pipe;
	int			pfds[2];
	pid_t		child_pid;
	pid_t		last_child_pid;

	h = minishell->cmd;
	prev_pipe = STDIN_FILENO;
	while (h->to_pipe == true)
	{
		if (pipe(pfds) == -1)
			exit(EXIT_FAILURE);
		child_pid = fork();
		if (child_pid == -1)
			exit(EXIT_FAILURE);
		if (child_pid == 0)
		{
			close(pfds[0]); // Close the unused read end of the pipe
			if (prev_pipe != STDIN_FILENO && dup2(prev_pipe, STDIN_FILENO) ==
				-1)
				exit(EXIT_FAILURE);
			if (dup2(pfds[1], STDOUT_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(pfds[1]);
			execve(h->path, h->args, ll_to_tab(envp));
			perror("execve failed");
			exit(EXIT_FAILURE);
		}
		else
		{
			close(prev_pipe); // Close only the read end of the previous pipe
			close(pfds[1]);
			prev_pipe = pfds[0];
			h = h->next;
		}
	}
	last_child_pid = fork();
	if (last_child_pid == -1)
		exit(EXIT_FAILURE);
	if (last_child_pid == 0)
	{
		if (prev_pipe != STDIN_FILENO && dup2(prev_pipe, STDIN_FILENO) == -1)
			exit(EXIT_FAILURE);
		execve(h->path, h->args, ll_to_tab(envp));
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
		close(prev_pipe);
	waitpid(last_child_pid, NULL, 0);
}
