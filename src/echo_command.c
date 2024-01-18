/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:48:14 by randre            #+#    #+#             */
/*   Updated: 2024/01/18 10:24:44 by randre           ###   ########.fr       */
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
				break;
			}
		}
		if (*val == 1 || *val == 2)
			break;
		j = -1;
		i++;
	}
}

void	handle_env(char **split_line, int i, int j)
{
	char	*name;
	int		len;
	int		old_j;
	char	*true_name;

	len = 0;
	if (!split_line[i][j + 1] || split_line[i][j + 1] == '"' || split_line[i][j + 1] == 39)
	{
		printf("$");
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
		printf("%s", getenv(name));
}

void	print_echo(char **split_line, int newline, int i)
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
				verify_end_quote(split_line, &in_quotes, i, j, split_line[i][j]);
			else if (split_line[i][j] == '$')
			{
				if (in_quotes != 1)
				{
					handle_env(split_line, i, j);
					break;
				}
				else
				{
					
					while (split_line[i][j] && split_line[i][j] != 39)
					{
						printf("%c", split_line[i][j]);
						j++;
					}
					break;
				}
			}
			else if ((split_line[i][j] != 92 && split_line[i][j] != '?' && split_line[i][j] != '"') && in_quotes == 0)
				printf("%c", split_line[i][j]);
			else if (in_quotes == 1 || in_quotes == 2)
				printf("%c", split_line[i][j]);
		}
		if (split_line[i + 1])
			printf(" ");
	}
	if (newline)
		printf("\n");
}

void	echo_command(char **split_line)
{
	if (!split_line[1])
		printf("\n");
	else if (ft_strcmp(split_line[1], "-n") && split_line[2])
		print_echo(split_line, 0, 1);
	else
	{
		if (ft_strcmp(split_line[1], "-n"))
			return ;
		print_echo(split_line, 1, 0);
	}
}
