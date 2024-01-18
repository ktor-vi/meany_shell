/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/01/18 10:36:37 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	**split_line;
	int		exit_flag;
	int		i;

	argc = 0;
	argv = NULL;
	while (1)
	{
		i = -1;
		line = readline("$ ");
		if (!ft_strcmp(line, ""))
		{
			split_line = ft_split(line, ' ');
			if (ft_strcmp(split_line[0], "exit"))
				exit_flag = 1;
			check_command(split_line, envp);
			while(split_line[++i])
				free(split_line[i]);
			free(split_line);
			if (exit_flag == 1)
				exit(0);
		}
		free(line);
	}
	return (0);
}
