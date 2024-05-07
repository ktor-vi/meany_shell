/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 11:09:44 by randre            #+#    #+#             */
/*   Updated: 2024/05/07 17:29:01 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <ctype.h>

char	*ft_strndup(char *str, int start, int end)
{
	char	*sstart;
	char	*s;

	s = malloc(((end - start) + 1) * sizeof(char));
	sstart = s;
	while (start != end)
	{
		*s = str[start];
		start++;
		s++;
	}
	*s = 0;
	return (sstart);
}

void	verify_quotes(char *line, int i, int *val)
{
	if ((*val == 1 && line[i] == '"') || (*val == 2 && line[i] == 39))
	{
		*val = 0;
		return ;
	}
	i++;
	while (line[i])
	{
		if (line[i] == '"')
		{
			*val = 1;
			return ;
		}
		else if (line[i] == 39)
		{
			*val = 2;
			return ;
		}
		else
			i++;
	}
	*val = 0;
	return ;
}

int	ft_isspecial(char c)
{
	if (c == '>' || c == '<' || c == '|')
		return (1);
	return (0);
}

char	**lexer(char *line, t_envs *envs)
{
	int		i;
	int		y;
	int		j;
	char	**split_line;
	int		in_quotes;

	j = 0;
	i = -1;
	y = 0;
	in_quotes = 0;
	split_line = ft_calloc((ft_strlen(line) + 1), sizeof(char *));
	while (line[++i])
	{
		if (line[i] == '"' || line[i] == 39)
			verify_quotes(line, i, &in_quotes);
		if (ft_isspecial(line[i]) && !in_quotes)
		{
			if (!isspace(line[i - 1]))
			{
				split_line[j] = ft_strndup(line, y, i);
				j++;
			}
			if ((line[i + 1] == line[i]) && line[i] != '|')
			{
				split_line[j] = ft_strndup(line, i, i + 2);
				i = i + 2;
			}
			else
			{
				split_line[j] = ft_strndup(line, i, i + 1);
				if (line[i] == '|' && line[i + 1] == '|')
					i = i + 2;
				else
					i++;
			}
			y = i;
			j = j + 1;
		}
		else if (isspace(line[i]) && !in_quotes)
		{
			split_line[j] = ft_strndup(line, y, i);
			i++;
			while (isspace(line[i]))
				i++;
			i--;
			if (line[i + 1] == 0)
				break;
			j++;
			y = i + 1;
		}
		if (in_quotes != 2)
		{
			if (line[i] == '$')
			{
				ft_printf(1, "BFR : %d\n", i);
				split_line[j] = ft_expand(line[i], &i, line, envs);
				ft_printf(1, "AFTR : %d\n", i);
				if (split_line[j])
					j++;
				if (line[i] == 0)
					break ;
				while (isspace(line[i]))
					i++;
				y = i;
				i--;
			}
		}
		if (line[i + 1] == 0)
		{
			split_line[j] = ft_strndup(line, y, i + 1);
			split_line[j + 1] = NULL;
			break ;
		}
	}
	return (split_line);
}
