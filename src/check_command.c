/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:45:36 by randre            #+#    #+#             */
/*   Updated: 2024/02/01 11:33:50 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_command(char **split_line, t_envs *envs)
{
	if (ft_equalstr(split_line[0], "echo"))
		echo_command(split_line);
	else if (ft_equalstr(split_line[0], "env"))
	{
		if (split_line[1])
		{
			write(1, "no arguments supported\n", 23);
			return ;
		}
		else
			printenv(envs->env);
	}
		else if (ft_equalstr(split_line[0], "export"))
		{
			if (split_line[1])
        export_cmd(envs, split_line[1]);
			else
				printexport(envs->exp);
		}
		else if (ft_equalstr(split_line[0], "cd")) 
		  cd_command(split_line);
		else if (ft_equalstr(split_line[0], "unset")) 
		  unset_cmd(envs, split_line[1]);
		else if (ft_equalstr(split_line[0], "pwd"))
		  pwd_command();
		else if (!ft_equalstr(split_line[0], "exit"))
		       write(1,
			"unknown command\n", 16);
	}
