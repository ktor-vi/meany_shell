/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:12:22 by vphilipp          #+#    #+#             */
/*   Updated: 2024/02/19 18:12:23 by vphilipp         ###   ########.fr       */
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
		execve(h->path, h->args, ll_to_tab(envs->env));
		if (errno == EFAULT)
			ft_printf(STDERR_FILENO, "command not found: %s\n", h->args[0]);
		else
			perror("execve failed");
		exit(EXIT_FAILURE);
	}
}

void	execute_last_command(t_command *h, int prev_pipe, t_envs *envs)
{
	pid_t	last_child_pid;

	last_child_pid = fork();
	if (last_child_pid == -1)
		forkfail_error();
	if (last_child_pid == 0)
	{
		if (prev_pipe != STDIN_FILENO && dup2(prev_pipe, STDIN_FILENO) == -1)
			dup2in_error();
		if (dup2(h->fd, STDOUT_FILENO) == -1)
			dup2out_error();
		close(prev_pipe);
		execve(h->path, h->args, ll_to_tab(envs->env));
		if (errno == EFAULT)
			ft_printf(STDERR_FILENO, "command not found: %s\n", h->args[0]);
		else
			perror("execve failed");
		exit(EXIT_FAILURE);
	}
	else
		close(prev_pipe);
	waitpid(last_child_pid, NULL, 0);
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
	while (h->to_pipe == true)
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
}
