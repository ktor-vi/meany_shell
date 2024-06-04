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

void here_doc(t_command *h, t_envs *envs, int *st)
{
    char *line;
    int here_pfds[2];

    if (pipe(here_pfds) == -1)
    {
        perror("pipe() error");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        write(st[1], "> ", 2);
        line = get_next_line(st[0]);
        if (line == NULL)
        {
            // Handle error or clean up resources
            close(here_pfds[0]);
            close(here_pfds[1]);
            break;
        }
        if (ft_strncmp(line, h->eof, ft_strlen(h->eof)) == 0
			&& ft_strlen(line) == ft_strlen(h->eof) + 1)
        {
            free(line);
            break;
        }
        write(here_pfds[1], line, ft_strlen(line));
        free(line);
    }
    close(here_pfds[1]);
    dup2(here_pfds[0], STDIN_FILENO);
    close(here_pfds[0]);    
    if(!pre_heredoc(h))
		handle_execve(h, envs);
}

void	execute_child(t_command *h, int prev_pipe, int pfds[2], t_envs *envs)
{
	pid_t	child_pid;
    int status;
	int			st[2];

	st[0] = dup(STDIN_FILENO);
	st[1] = dup(STDOUT_FILENO);
	child_pid = fork();
	if (child_pid == -1)
		forkfail_error();
	if (child_pid == 0)
	{
		if (prev_pipe != STDIN_FILENO && dup2(prev_pipe, STDIN_FILENO) == -1)
			dup2in_error();
		if (dup2(pfds[1], STDOUT_FILENO) == -1)
			dup2out_error();
		if (h->heredoc == true)
			here_doc(h, envs, st);
		else
			handle_execve(h, envs);
		close(pfds[0]);
		close(pfds[1]);
		close(prev_pipe);
		exit(EXIT_FAILURE);
	}
	else
		waitpid(child_pid, &status, 0);
}

void	execute_last_command(t_command *h, int prev_pipe, t_envs *envs)
{
	pid_t	last_child_pid;
	int		pfds[2];
	int			st[2];

	st[0] = dup(STDIN_FILENO);
	st[1] = dup(STDOUT_FILENO);
	last_child_pid = fork();
	if (last_child_pid == -1)
		forkfail_error();
	if (last_child_pid == 0)
	{
		if (prev_pipe != STDIN_FILENO && dup2(prev_pipe, STDIN_FILENO) == -1)
			dup2in_error();
		if (dup2(h->fd, STDOUT_FILENO) == -1)
			dup2out_error();
		if (h->heredoc == true)
			here_doc(h, envs, st);
		else
			handle_execve(h, envs);
		close(prev_pipe);
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
}
