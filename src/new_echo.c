/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 00:56:33 by randre            #+#    #+#             */
/*   Updated: 2024/05/22 11:17:39 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_n(char *line)
{
	int	i;

	i = 0;
	if (!line || line[0] != '-')
		return (0);
	while (line[++i] != 0)
	{
		if (line[i] != 'n')
			return (0);
	}
	return (1);
}

inline static int	is_special(char c)
{
	return (c == '\\' || c == '"' || c == 39 || c == '?' || c == '$');
}

static void	true_print(t_command *cmd, int i)
{
	int	y;

	y = -1;
	while (cmd->args[i][++y] != 0)
	{
		if (is_special(cmd->args[i][y]))
		{
			if (cmd->arg[i]->in_quotes != 0)
				ft_printf(cmd->fd, "%c", cmd->args[i][y]);
		}
		else
			ft_printf(cmd->fd, "%c", cmd->args[i][y]);
	}
}

static void	print_echo(t_command *cmd, int i, int newline, char **split_line)
{
	while (is_n(split_line[i]) && split_line[i])
		i++;
	if (!split_line[i])
	{
		if (newline)
			write(cmd->fd, "\n", 1);
		return ;
	}
	while (cmd->args[i])
	{
		true_print(cmd, i);
		if (cmd->args[i + 1])
			ft_printf(cmd->fd, " ");
		i++;
	}
	if (newline)
		ft_printf(cmd->fd, "\n");
}

void	echo_command(char **split_line, t_command *cmd)
{
	if (!split_line[1])
		ft_printf(cmd->fd, "\n");
	else if (is_n(split_line[1]))
		print_echo(cmd, 2, 0, split_line);
	else
		print_echo(cmd, 1, 1, split_line);
}