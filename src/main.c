/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/06/18 14:46:51 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int	g_exit_codes;

t_envs	*init(int argc, char **argv, char **envp, char *line)
{
	t_envs	*envs;

	(void)argc;
	(void)argv;
	envs = build_envs(envp);
	line = NULL;
	return (envs);
}

void	reset(char *line, t_envs *envs)
{
	if (line)
		reset_line(line);
	else
		kb_quit(envs);
}

void	exec_cmd(t_minishell *minishell, char **split_line, t_envs *envs)
{
	minishell = populate_cmds(split_line, envs);
	minishell->st_in = dup(STDIN_FILENO);
	execute_pipes(minishell, envs);
	dup2(minishell->st_in, STDIN_FILENO);
	free_tab(split_line);
	close(minishell->st_in);
	clean_minishell(minishell);
}

int	main(int argc, char **argv, char **envp)
{
	char		**split_line;
	char		*line;
	t_envs		*envs;
	t_minishell	*minishell;

	line = NULL;
	minishell = NULL;
	envs = init(argc, argv, envp, line);
	g_exit_codes = 0;
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
		reset(line, envs);
	}
	return (0);
}
