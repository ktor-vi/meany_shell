/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktorvi <ktorvi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 06:51:50 by vphilipp          #+#    #+#             */
/*   Updated: 2024/02/17 13:32:44by ktorvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	child_process(int prev_pipe, int pfds[2], t_command *h, t_entry *envp)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		forkfail_error();
	if (child_pid == 0)
	{
		close(pfds[0]);
		if (prev_pipe != STDIN_FILENO && dup2(prev_pipe, STDIN_FILENO) == -1)
			dup2in_error();
		if (dup2(pfds[1], STDOUT_FILENO) == -1)
			dup2out_error();
		close(pfds[1]);
		execve(h->path, h->args, ll_to_tab(envp));
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

void	execute_child(t_command *h, int prev_pipe, int pfds[2], t_entry *envp)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		forkfail_error();
	if (child_pid == 0)
	{
		close(pfds[0]);
		if (prev_pipe != STDIN_FILENO && dup2(prev_pipe, STDIN_FILENO) == -1)
			dup2in_error();
		close(prev_pipe);
		if (dup2(pfds[1], STDOUT_FILENO) == -1)
			dup2out_error();
		close(pfds[1]);
		execve(h->path, h->args, ll_to_tab(envp));
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

void	execute_last_command(t_command *h, int prev_pipe, t_entry *envp)
{
	pid_t	last_child_pid;

	last_child_pid = fork();
	if (last_child_pid == -1)
		forkfail_error();
	if (last_child_pid == 0)
	{
		if (prev_pipe != STDIN_FILENO && dup2(prev_pipe, STDIN_FILENO) == -1)
			dup2in_error();
		execve(h->path, h->args, ll_to_tab(envp));
		perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
	{
		close(prev_pipe);
	}
	waitpid(last_child_pid, NULL, 0);
}

void	execute_pipes(t_minishell *minishell, t_entry *envp)
{
	t_command	*h;
	int			prev_pipe;
	int			pfds[2];

	h = minishell->cmd;
	prev_pipe = STDIN_FILENO;
	while (h->to_pipe == true)
	{
		create_pipe(pfds);
		execute_child(h, prev_pipe, pfds, envp);
		parent_process(prev_pipe, pfds, &h);
		prev_pipe = pfds[0];
	}
	execute_last_command(h, prev_pipe, envp);
}
