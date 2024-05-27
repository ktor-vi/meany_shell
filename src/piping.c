/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   piping.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 18:12:22 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/27 14:20:18 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	here_doc(t_command *h, t_envs *envs, int *pfds)
{
	char	*line;

	if (pipe(pfds) == -1)
	{
		perror("pipe() error");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = get_next_line(STDIN_FILENO);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, h->eof, ft_strlen(h->eof)) == 0
			&& ft_strlen(line) == ft_strlen(h->eof) + 1)
		{
			free(line);
			break ;
		}
		write(pfds[1], line, ft_strlen(line));
		free(line);
	}
	close(pfds[1]);
	dup2(pfds[0], STDIN_FILENO);
	close(pfds[0]);
}

void	child_process(t_command *h, int prev_pipe, int pfds[2], t_envs *envs)
{
	if (prev_pipe != STDIN_FILENO)
	{
		handle_dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (h->next)
	{
		close(pfds[0]);
		handle_dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
	}
	if (h->heredoc == 1)
	{
		here_doc(h, envs, pfds);
	}
	if (!pre_heredoc(h))
		handle_execve(h, envs);
	exit(EXIT_FAILURE);
}

void	execute_child(t_command *h, int prev_pipe, int pfds[2], t_envs *envs)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		forkfail_error();
	if (child_pid == 0)
		child_process(h, prev_pipe, pfds, envs);
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
	if (h->next)
		close(pfds[1]);
}

void	execute_builtin(t_command *h, int prev_pipe, int pfds[2], t_envs *envs)
{
	int	temp_fd;

	temp_fd = dup(STDOUT_FILENO);
	if (prev_pipe != STDIN_FILENO)
	{
		handle_dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	if (h->next)
	{
		handle_dup2(pfds[1], STDOUT_FILENO);
		close(pfds[1]);
	}
	handle_builtins(h, envs);
	dup2(temp_fd, STDOUT_FILENO);
	close(temp_fd);
}

void	execute_pipes(t_minishell *minishell, t_envs *envs)
{
	t_command	*h;
	int			prev_pipe;
	int			pfds[2];
	pid_t		last_pid;

	h = minishell->cmd;
	prev_pipe = STDIN_FILENO;
	while (h != NULL)
	{
		if (h->next && pipe(pfds) == -1)
			pipe_error();
		if (is_builtin(h))
			execute_builtin(h, prev_pipe, pfds, envs);
		else
		{
			execute_child(h, prev_pipe, pfds, envs);
			last_pid = h->pid;
		}
		if (prev_pipe != STDIN_FILENO)
			close(prev_pipe);
		if (h->next)
			close(pfds[1]);
		prev_pipe = h->next ? pfds[0] : STDIN_FILENO;
		h = h->next;
	}
	if (h == NULL && last_pid != -1)
		wait(NULL);
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
}
