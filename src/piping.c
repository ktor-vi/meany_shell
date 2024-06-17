/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:12:22 by vphilipp          #+#    #+#             */
/*   Updated: 2024/06/17 11:44:52 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	execute_child(t_command *h, int prev_pipe, int pfds[2], t_envs *envs)
{
	int	st[2];
	int	status;

	preserve_st(st);
	h->pid = fork();
	if (h->pid == -1)
		forkfail_error();
	if (h->pid == 0)
	{
		close(pfds[0]);
		if (prev_pipe != STDIN_FILENO && dup2(prev_pipe, STDIN_FILENO) == -1)
			dup2in_error();
		if (dup2(pfds[1], STDOUT_FILENO) == -1)
			dup2out_error();
		close(pfds[1]);
		if (h->heredoc == true)
			here_doc(h, envs, st);
		else
			handle_execve(h, envs);
		close(prev_pipe);
		exit(EXIT_FAILURE);
	}
}

void	execute_last_command(t_command *h, int prev_pipe, t_envs *envs)
{
	int	pfds[2];
	int	st[2];
	int	exit_code;

	preserve_st(st);
	if (!h->path)
		return (no_path(h));
	h->pid = fork();
	if (h->pid == -1)
		forkfail_error();
	if (h->pid == 0)
		last_cmd_child(prev_pipe, h, envs, st);
	close(prev_pipe);
}

void	execute_builtin(t_command *h, int prev_pipe, int pfds[2], t_envs *envs)
{
	int	temp_fd;

	temp_fd = dup(STDOUT_FILENO);
	if (prev_pipe != STDIN_FILENO && dup2(prev_pipe, STDIN_FILENO) == -1)
		dup2in_error();
	close(prev_pipe);
	if (dup2(pfds[1], STDOUT_FILENO) == -1)
		dup2out_error();
	handle_builtins(h, envs);
	dup2(temp_fd, STDOUT_FILENO);
	close(temp_fd);
}

void	execute_last_builtin(t_command *h, int prev_pipe, t_envs *envs)
{
	int	temp_fd;

	if (prev_pipe != STDIN_FILENO && dup2(prev_pipe, STDIN_FILENO) == -1)
		dup2in_error();
	temp_fd = dup(STDOUT_FILENO);
	handle_builtins(h, envs);
	dup2(temp_fd, STDOUT_FILENO);
	close(temp_fd);
}

void	execute_pipes(t_minishell *minishell, t_envs *envs)
{
	t_command	*h;
	int			prev_pipe;
	int			pfds[2];

	h = minishell->cmd;
	prev_pipe = STDIN_FILENO;
	while (h->next)
	{
		create_pipe(pfds);
		if (!is_builtin(h))
			execute_child(h, prev_pipe, pfds, envs);
		else
			execute_builtin(h, prev_pipe, pfds, envs);
		parent_process(prev_pipe, pfds);
		prev_pipe = pfds[0];
		h = h->next;
	}
	if (!is_builtin(h))
		execute_last_command(h, prev_pipe, envs);
	else		
		execute_last_builtin(h, prev_pipe, envs);
	waitpid(h->pid, &g_exit_codes, 0);
	h = h->prev;
	while (h)
	{
		waitpid(h->pid, NULL, 0);
		h = h->prev;
	}
}
