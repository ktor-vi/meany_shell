/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/07/25 13:53:25 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int		g_exit_codes;

t_envs	*init(int argc, char **argv, char **envp)
{
	t_envs	*envs;

	(void)argc;
	(void)argv;
	envs = build_envs(envp);
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

int	line_empty(char *line)
{
	int	l;
	int	i;
	int	sw;

	i = 0;
	l = 0;
	sw = 0;
	l = ft_strlen(line);
	while ((line[i] == ' ') || (line[i] == '	'))
		i++;
	return (i == l);
}

int	main(int argc, char **argv, char **envp)
{
	char		**split_line;
	char		*line;
	t_envs		*envs;
	t_minishell	*minishell;

	line = NULL;
	minishell = NULL;
	envs = init(argc, argv, envp);
	g_exit_codes = 0;
	while (true)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		line = readline("$ ");
		signal(SIGINT, handle_sigint2);
		if (line && !ft_equalstr(line, "") && !line_empty(line))
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
