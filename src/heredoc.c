/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:10:42 by vphilipp          #+#    #+#             */
/*   Updated: 2024/06/12 16:02:04 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

void	ft_here_doc_last(t_command *h, t_envs *envs)
{
	char	*line;
	int		pid;
	int		pfds[2];
	int		status;

	line = NULL;
	if (pipe(pfds) == -1)
	{
		perror("pipe() error");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		close(pfds[0]);
		while (ft_strcmp(line, h->eof) != 0)
		{
			write(pfds[1], line, ft_strlen(line));
			free(line);
			line = readline("> ");
			ft_printf(1, "test\n");
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pfds[1]);
		wait(&status);
		g_exit_codes = WEXITSTATUS(status);
		if (dup2(pfds[0], STDIN_FILENO) == -1)
		{
			perror("dup2() error");
			exit(EXIT_FAILURE);
		}
		execve(h->path, h->args, ll_to_tab(envs->env));
	}
}

void	ft_here_doc_piped(t_command *h, t_envs *envs, int *pfds)
{
	char	*line;
	int		pid;
	int		status;

	line = NULL;
	if (pipe(pfds) == -1)
	{
		perror("pipe() error");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		write(STDIN_FILENO, "ok\n", 3);
		while (ft_strncmp(line, h->eof, ft_strlen(h->eof)) != 0)
		{
			write(pfds[1], line, ft_strlen(line));
			free(line);
			line = readline("> ");
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pfds[1]);
		if (dup2(pfds[0], STDIN_FILENO) == -1)
		{
			perror("dup2() error");
			exit(EXIT_FAILURE);
		}
		waitpid(pid, &status, 0);
		execve(h->path, h->args, ll_to_tab(envs->env));
		g_exit_codes = WEXITSTATUS(status);
	}
}

void	here_doc(t_command *h, t_envs *envs, int *st)
{
	char	*line;
	int		here_pfds[2];

	create_pipe(here_pfds);
	while (1)
	{
		write(st[1], "> ", 2);
		line = get_next_line(st[0]);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, h->eof, ft_strlen(h->eof)) == 0
			&& ft_strlen(line) == ft_strlen(h->eof) + 1)
			break ;
		write(here_pfds[1], line, ft_strlen(line));
		free(line);
	}
	if (line)
		free(line);
	close(here_pfds[1]);
	dup2(here_pfds[0], STDIN_FILENO);
	close(here_pfds[0]);
	if (!pre_heredoc(h))
		handle_execve(h, envs);
}
