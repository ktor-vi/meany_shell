/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_main.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/05/29 12:43:47 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int		g_exit_codes[2];

t_envs	*init(int argc, char **argv, char **envp, char *line)
{
	t_envs	*envs;

	(void)argc;
	(void)argv;
	envs = build_envs(envp);
	line = NULL;
	return (envs);
}

void	reset(char *line)
{
	if (line)
		reset_line(line);
	else
		kb_quit();
}

void	exec_cmd(t_minishell *minishell, char **split_line, t_envs *envs)
{
	minishell = populate_cmds(split_line, envs);
	minishell->st_in = dup(STDIN_FILENO);
	execute_pipes(minishell, envs);
	dup2(minishell->st_in, STDIN_FILENO);
	free_tab(split_line);
	close(minishell->st_in);
}

int	main(int argc, char **argv, char **envp)
{
	char		**split_line;
	char		*line;
	t_envs		*envs;
	t_minishell	*minishell;

	envs = init(argc, argv, envp, line);
	while (true)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		line = readline("$ ");
		signal(SIGINT, handle_sigint2);
		if (line && !ft_equalstr(line, ""))
		{
			add_history(line);
			split_line = lexer(line, envs);
			if (split_line)
				exec_cmd(minishell, split_line, envs);
		}
		reset(line);
	}
	return (0);
}
