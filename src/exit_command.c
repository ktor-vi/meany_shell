/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 09:29:05 by vphilipp          #+#    #+#             */
/*   Updated: 2024/08/12 09:29:08 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int numeric_exit(char *str)
{
	int i;
	int over;

	i = 0;
	over = ft_atoi(str);
	if (str[0] == '\0')
		return (1);
	if ((str[0] == '-' || str[0] == '+') && str[1] != '\0')
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	if ((over == 0 || over == -1) && ft_strlen(str) > 2)
		return (1);
	return (0);
}

static int exit_atoi(const char *str)
{
	unsigned char result;
	int i;
	int sign;

	result = 0;
	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	if (!ft_isdigit(str[i]))
		return (0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - '0');
	}
	return (result * sign);
}

void exitshell_command(t_command *cmd, t_envs *envs)
{
	if (!cmd->args[1])
	{
		g_exit_codes = 0;
		kb_quit(envs);
	}
	if (cmd->args[1])
	{
		if (numeric_exit(cmd->args[1]))
		{
			ft_printf(2, "exit\nbash: line 1: exit: %s: numeric argument required\n",
					  cmd->args[1]);
			g_exit_codes = 2;
			kb_quit(envs);
		}
		else
		{
			g_exit_codes = exit_atoi(cmd->args[1]);
			kb_quit(envs);
		}
	}
	else if (cmd->args[2])
	{
		ft_printf(2, "exit: too many arguments\n");
		return;
	}
}
