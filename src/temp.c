/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 13:07:03 by randre            #+#    #+#             */
/*   Updated: 2024/02/20 13:48:37 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>

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

int	redirect_handle(char **split_line, int *j, int *i)
{
	int	fd;
	int	y;
	int	val;
	int	start;

	if (split_line[*i][*j + 1] == NULL)
	{
		fd = open(split_line[*i + 1], O_WRONLY);
		if (fd < 0)
		{
			fd = open(split_line[*i + 1], O_CREAT, 0666);
			close(fd);
			fd = open(split_line[*i + 1], O_WRONLY);
		}
		*i = *i + 2;
		return (fd);
	}
	else
	{
		start = *j;
		y = 0;
		val = 0;
		while (split_line[*i][*j])
		{
			verify_end_quote(split_line, &val, *i, *j, split_line[*i][*j]);
			if (split_line[*i][*j] != '|' && val == 0)
				break;
			*j = *j + 1;
		}
		fd = open(ft_substr(split_line[*i], start, *j - start), O_WRONLY);
		if (fd < 0)
		{
			fd = open(ft_substr(split_line[*i], start, *j - start), O_CREAT, 0666);
			close(fd);
			fd = open(ft_substr(split_line[*i], start, *j - start), O_WRONLY);
		}
		return (fd);
	}
}

t_minishell	*populate(char **split_line, t_envs *envs)
{
	int			i;
	int			j;
	int			fd;
	int			val;
	int			args;
	t_minishell	*minishell;

	i = -1;
	j = -1;
	args = 0;
	fd = STDOUT_FILENO;
	minishell = malloc(sizeof(t_minishell));
	minishell->cmd = NULL;
	while (split_line[++i] != NULL)
	{
		j = -1;
		fd = STDOUT_FILENO;
		while (split_line[i][++j] != NULL)
		{
			verify_end_quote(split_line, &val, i, j, split_line[i][j]);
			if (val == 0)
			{
				if (ft_strchr(split_line[j], '|') != NULL || ft_strchr(split_line[j], '>') != NULL)
				{
					while (split_line[i][j] != '|' && split_line[i][j] != '>')
						j++;
					if (split_line[i][j] == '>')
					{
						fd = redirect_handle(split_line, &j, &i);
						if (j > ft_strlen(split_line[i]) || ft_strlen(split_line[i]) == 0)
							break;
					}
					if (split_line[i][j] == '|')
						ft_cmd_addb(&minishell, new_command(split_line, envs, i, j, fd));	
				}
				else
					args++;
			}
			if (ft_strlen(split_line[i]) == 0)
				break;
		}
	}
	ft_cmd_addb(&minishell, new_command(split_line, envs, i, j, fd));
	return (minishell);
}


t_command	*new_command(char **split_line, t_envs *envs, int s, int e, int fd)
{
	t_command	*new;
	int			i;

	i = 0;
	new = malloc(sizeof(t_command));
	new->args_ct = e - s;
	new->fd = fd;
	new->path = get_cmdpath(split_line[s], envs->env);
	if (s == e)
	{
		new->args[i] = ft_strdup(split_line[s + i]);
		new->args_ct = 1;
		return (new);
	}
	else
		new->args = malloc((e - s + 1) * sizeof(char *));
	while (i < new->args_ct)
	{
		new->args[i] = ft_strdup(split_line[s + i]);
		i++;
	}
	if (ft_equalstr(split_line[e], "|"))
		new->to_pipe = true;
	new->args[i] = NULL;
	return (new);
}
