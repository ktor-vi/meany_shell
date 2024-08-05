/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:45:36 by randre            #+#    #+#             */
/*   Updated: 2024/06/18 14:45:59 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_builtin_char(char **split_line)
{
	write(1, split_line[0], 1);
	if (!split_line || !split_line[0])
		return (0);
	if (ft_equalstr(split_line[0], "echo"))
		return (1);
	else if (ft_equalstr(split_line[0], "env"))
		return (1);
	else if (ft_equalstr(split_line[0], "export"))
		return (1);
	else if (ft_equalstr(split_line[0], "cd"))
		return (1);
	else if (ft_equalstr(split_line[0], "unset"))
		return (1);
	else if (ft_equalstr(split_line[0], "pwd"))
		return (1);
	else if (!ft_equalstr(split_line[0], "exit"))
		return (1);
	else
		return (0);
}

int	is_builtin_char_pos(char **split_line, int pos)
{
	if (ft_equalstr(split_line[pos], "echo"))
		return (1);
	else if (ft_equalstr(split_line[pos], "env"))
		return (1);
	else if (ft_equalstr(split_line[pos], "export"))
		return (1);
	else if (ft_equalstr(split_line[pos], "cd"))
		return (1);
	else if (ft_equalstr(split_line[pos], "unset"))
		return (1);
	else if (ft_equalstr(split_line[pos], "pwd"))
		return (1);
	else if (!ft_equalstr(split_line[pos], "exit"))
		return (1);
	else
		return (0);
}

// static int	is_word(char *word)
// {

// }
static int	builtins_next(t_command *cmd, t_envs *envs)
{
	if (ft_equalstr(cmd->args[0], "export"))
	{
		if (cmd->args[1] && !ft_equalstr(cmd->args[1], ">"))
			export_cmd(envs, cmd->args);
		else
			printexport(envs->exp, cmd);
	}
	else if (ft_equalstr(cmd->args[0], "cd"))
		cd_command(cmd->args);
	else if (ft_equalstr(cmd->args[0], "unset"))
		unset_cmd(envs, cmd->args[1]);
	else if (ft_equalstr(cmd->args[0], "pwd"))
		pwd_command(cmd);
	else if (ft_equalstr(cmd->args[0], "exit"))
	   exitshell_command(cmd, envs);
	else
		return (0);
	return (1);
}

int	handle_builtins(t_command *cmd, t_envs *envs)
{
	while (cmd != NULL)
	{
		if (ft_equalstr(cmd->args[0], "echo"))
			echo_command(cmd->args, cmd);
		else if (ft_equalstr(cmd->args[0], "env"))
		{
			if (cmd->args[1] && !ft_equalstr(cmd->args[1], ">"))
			{
				write(1, "no arguments supported\n", 14);
				g_exit_codes = 2;
				return (1);
			}
			printenv(envs->env, cmd);
		}
		else if (builtins_next(cmd, envs) == 0)
			return (0);
		cmd = cmd->next;
	}
	return (1);
}

int	is_builtin(t_command *cmd)
{
	if (ft_equalstr(cmd->args[0], "echo"))
		return (1);
	else if (ft_equalstr(cmd->args[0], "env"))
		return (1);
	else if (ft_equalstr(cmd->args[0], "export"))
		return (1);
	else if (ft_equalstr(cmd->args[0], "cd"))
		return (1);
	else if (ft_equalstr(cmd->args[0], "unset"))
		return (1);
	else if (ft_equalstr(cmd->args[0], "pwd"))
		return (1);
	else if (ft_equalstr(cmd->args[0], "exit"))
		return (1);
	else
		return (0);
}
