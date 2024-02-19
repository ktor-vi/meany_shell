/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:48:14 by randre            #+#    #+#             */
/*   Updated: 2024/02/19 11:22:37 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	verify_end_quote(char **split_line, int *val, int i, int j, char c)
{
	if (*val == 1 && c == 39)
	{
		*val = 0;
		return ;
	}
	else if (*val == 2 && c == '"')
	{
		*val = 0;
		return ;
	}
	while (split_line[i])
	{
		while (split_line[i][++j])
		{
			if (split_line[i][j] == c)
			{
				if (split_line[i][j] == '"')
					*val = 2;
				else
					*val = 1;
				break ;
			}
		}
		if (*val == 1 || *val == 2)
			break ;
		j = -1;
		i++;
	}
}

void	handle_env(char **split_line, int i, int j, int fd)
{
	char	*name;
	int		len;
	int		old_j;
	char	*true_name;

	len = 0;
	if (!split_line[i][j + 1] || split_line[i][j + 1] == '"' || split_line[i][j
		+ 1] == 39)
	{
		ft_printf(fd, "$");
		return ;
	}
	old_j = j;
	while (split_line[i][++j] != '\0')
		len++;
	name = malloc((len + 1) * sizeof(char));
	len = -1;
	while (split_line[i][++old_j] && split_line[i][old_j] != '"')
		name[++len] = split_line[i][old_j];
	name[len + 1] = '\0';
	true_name = getenv(name);
	free(name);
	if (true_name)
		ft_printf(fd, "%s", true_name);
}

void	print_echo(char **split_line, int newline, int i, int fd)
{
	int	in_quotes;
	int	j;

	in_quotes = 0;
	while (split_line[++i])
	{
		j = -1;
		while (split_line[i][++j])
		{
			if (split_line[i][j] == '"' || split_line[i][j] == 39)
				verify_end_quote(split_line, &in_quotes, i, j,
					split_line[i][j]);
			else if (split_line[i][j] == '$')
			{
				if (in_quotes != 1)
				{
					handle_env(split_line, i, j, fd);
					break ;
				}
				else
				{
					while (split_line[i][j] && split_line[i][j] != 39)
					{
						ft_printf(fd, "%c", split_line[i][j]);
						j++;
					}
					break ;
				}
			}
			else if ((split_line[i][j] != 92 && split_line[i][j] != '?'
					&& split_line[i][j] != '"') && in_quotes == 0)
				ft_printf(fd, "%c", split_line[i][j]);
			else if (in_quotes == 1 || in_quotes == 2)
				ft_printf(fd, "%c", split_line[i][j]);
		}
		if (split_line[i + 1])
			ft_printf(fd, " ");
	}
	if (newline)
		ft_printf(fd, "\n");
}

void	echo_command(char **split_line, t_command *cmd)
{
	if (!split_line[1])
		ft_printf(cmd->fd, "\n");
	else if (ft_equalstr(split_line[1], "-n") && split_line[2])
		print_echo(split_line, 0, 1, cmd->fd);
	else
	{
		if (ft_equalstr(split_line[1], "-n"))
			return ;
		print_echo(split_line, 1, 0, cmd->fd);
	}
}
