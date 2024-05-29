/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/05/29 11:44:20 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int	main(int argc, char **argv, char **envp)
{
	char		**split_line;
	char		*line;
	t_envs		*envs;
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	envs = build_envs(envp);
	line = NULL;
	while (true)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		line = readline("$ ");
		signal(SIGINT, handle_sigint2);
		if (!line)
			kb_quit();
		else if (!ft_equalstr(line, ""))
		{
			add_history(line);
			split_line = lexer(line, envs);
			if (split_line)
			{
				minishell = populate_cmds(split_line, envs);
				minishell->st_in = dup(STDIN_FILENO);
				execute_pipes(minishell, envs);
				dup2(minishell->st_in, STDIN_FILENO);
				free_tab(split_line);
				close(minishell->st_in);
			}
		}
		if (line)
			reset_line(line);
	}
	return (0);
}
