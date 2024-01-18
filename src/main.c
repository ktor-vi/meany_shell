/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/01/18 15:16:20 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_SIGINT(int sig)
{
	sig = 0;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_SIGQUIT(int sig)
{
	sig = 0;
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	char	**split_line;
	char	*line;
	int		exit_flag;
	int		i;

	argc = 0;
	argv = NULL;
	line = NULL;
	signal(SIGINT, handle_SIGINT);
	signal(SIGQUIT, handle_SIGQUIT);
	while (1)
	{
		i = -1;
		line = readline("$ ");
		if (line && !ft_strcmp(line, ""))
		{
			split_line = ft_split(line, ' ');
			if (ft_strcmp(split_line[0], "exit"))
				exit_flag = 1;
			add_history(line);
			check_command(split_line, envp);
			while(split_line[++i])
				free(split_line[i]);
			free(split_line);
		}
		if (line)
			free(line);
		else
			exit_flag = 1;
		if (exit_flag == 1)
		{
			rl_clear_history();
			exit(0);
		}
	}
	return (0);
}
