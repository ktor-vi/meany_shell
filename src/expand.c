/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:43:02 by randre            #+#    #+#             */
/*   Updated: 2024/05/30 17:05:48 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <ctype.h>

static int	ft_bfrspace(char *line, int i)
{
	int	y;

	y = 0;
	if (!line)
		return (0);
	while (line[i] && !isspace(line[i]) && line[i] != 39 && line[i] != '"')
	{
		y++;
		i++;
	}
	return (y);
}

char	*ft_copy(char *line, int **i)
{
	char	*true_line;
	int		length;
	int		y;

	length = ft_bfrspace(line, **i);
	if (!length)
		return (NULL);
	true_line = malloc((length + 1) * sizeof(char));
	if (!true_line)
		return (NULL);
	y = 0;
	while (length--)
	{
		true_line[y] = line[**i];
		**i += 1;
		y++;
	}
	true_line[y] = 0;
	return (true_line);
}

char	*ft_expand(char *line, t_lexer_state *state, t_envs *envs)
{
	char	*true_line;
	int		start;
	int		end;
	char	*res;

	if (line[state->i] == '$')
	{
		start = ++state->i;
		end = start;
		while (line[end] && (line[end] != '"' && !isspace(line[end])
				&& !isspecial(line[end])))
			end++;
		true_line = ft_strndup(line, start, end);
		if (!true_line)
			return (0);
		res = envs_search(envs, true_line);
		state->i = end;
		if (res)
			return (res);
	}
	return (NULL);
}
