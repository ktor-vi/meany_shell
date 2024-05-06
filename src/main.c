/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/05/06 15:22:20 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigint2(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
	}
}
void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
}
int g_exit_codes[2];

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
	minishell = malloc(1 * sizeof(t_minishell));
	mini_init(minishell);
	while (true)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		line = readline("$ ");
		minishell->args = ft_strtrim(line, " ");
		free(line);
		signal(SIGINT, handle_sigint2);
		if (!minishell->args)
			kb_quit();
		else if (!ft_equalstr(minishell->args, ""))
		{
			add_history(minishell->args);
			if (!count_quotes(minishell->args))
				ft_error(2);
			if (!token_reader(minishell))
				ft_error(1);
			//free(line);
			//minishell = populate(split_line, envs);
			//minishell->st_in = dup(STDIN_FILENO);
			//execute_pipes(minishell, envs);
			//dup2(minishell->st_in, STDIN_FILENO);
			//free_tab(split_line);
		}
		if (minishell->args)
			reset_line(minishell->args);
	}
	return (0);
}
