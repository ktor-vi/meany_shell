/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:45:36 by randre            #+#    #+#             */
/*   Updated: 2024/01/18 10:34:44 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_command(char **split_line, char **envp)
{
	if (ft_strcmp(split_line[0], "echo"))
		echo_command(split_line);
	else if (ft_strcmp(split_line[0], "env"))
	{
		if (split_line[1])
		{
			write(1, "bad arguments\n", 14);
			return ;
		}
		else
			env_command(envp);
	}
	else if (!ft_strcmp(split_line[0], "exit"))
		write(1, "unknown command\n", 16);
}