/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:10:42 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/27 14:10:43 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

void	ft_here_doc_last(t_command *h, t_envs *envs)
{
	char	*line;
	int		pid;
	int		pfds[2];

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
		wait(NULL);
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
		waitpid(pid, NULL, 0);
		execve(h->path, h->args, ll_to_tab(envs->env));
	}
}
