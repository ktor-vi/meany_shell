/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:43:02 by randre            #+#    #+#             */
/*   Updated: 2024/06/12 15:40:25 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <ctype.h>

static char	*envs_search_exp(t_envs *envs, char *to_find)
{
	t_entry	*entry;

	entry = envs->exp;
	while (entry->next != NULL)
	{
		if (ft_equalstr(entry->name, to_find))
		{
			ft_strlen(entry->value);
			return (ft_strdup(entry->value));
		}
		entry = entry->next;
	}
	return (NULL);
}

static int	ft_bfrspace(char *line, int i)
{
	int	y;

	y = 0;
	if (!line)
		return (0);
	while (line[i] && !ft_isspace(line[i]) && line[i] != 39 && line[i] != '"')
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
		while (line[end] && (line[end] != '"' && !ft_isspace(line[end])
				&& !ft_isspecial(line[end])))
			end++;
		true_line = ft_strndup(line, start, end);
		if (!true_line)
			return (0);
		res = envs_search_exp(envs, true_line);
		free(true_line);
		state->i = end;
		if (res)
			return (res);
		else if (line[start] == '?' && !line[start + 1])
			return (get_exit_code());
	}
	return (NULL);
}
