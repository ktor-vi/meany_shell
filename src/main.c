/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/02/01 16:34:33 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_SIGINT(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_SIGQUIT(int sig)
{
	if (sig == SIGQUIT)
		return ;
}

int	main(int argc, char **argv, char **envp)
{
	char		**split_line;
	char		*line;
	int			i;
	int			j;
	t_envs		*envs;
	t_minishell	*minishell;

	(void)argc;
	(void)argv;
	envs = build_envs(envp);
	line = NULL;
	signal(SIGINT, handle_SIGINT);
	signal(SIGQUIT, handle_SIGQUIT);
	while (true)
	{
			write(1, "n\n", 2);
		i = -1;
		j = -1;
		line = readline("$ ");
		if(!line)
			write(1, "k\n", 2);
		if (line && !ft_equalstr(line, ""))
		{
			split_line = ft_split(line, ' ');
			add_history(line);
			minishell = populate(split_line, envs);
			if (!handle_builtins(minishell->cmd, envs))
				execute_pipes(minishell, envs->env);
			while (split_line[++i])
				free(split_line[i]);
			free(split_line);
			// while (minishell->cmd->args[++j])
			// 	free(minishell->cmd->args[j]);
			// free(minishell->cmd->args);
		}
		if(line)
		{
			write(1, "o\n", 2);
			free(line);
			line = (char *)NULL;
		}
		else
		{
			// write(1, "y\n", 2);
			rl_clear_history();
			exit(0);
		}
	}
	return (0);
}
