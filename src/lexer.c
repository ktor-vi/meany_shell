/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:45:22 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/30 14:55:38 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

char	*ft_strndup(char *str, int start, int end)
{
	int		i;
	int		len;
	char	*s;

	i = -1;
	if (start >= end)
		return (NULL);
	len = end - start;
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while(++i < len)
		s[i] = str[start + i];
	s[len] = '\0';
	printf("ft_strndup: Created substring '%s' from indices [%d, %d]\n", s,
		start, end);
	return (s);
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
	return (c == '>' || c == '<' || c == '|');
}

int	handle_end_of_line(char *line, t_lexer_state *state)
{
	if (line[state->i + 1] == 0)
	{
		state->split_line[state->j] = ft_strndup(line, state->y, state->i + 1);
		state->split_line[state->j + 1] = NULL;
		printf("handle_end_of_line: Added end of line substring, j=%d, i=%d,\
			y=%d\n",
				state->j,
				state->i,
				state->y);
		return (-1);
	}
	return (0);
}

char	**lexer(char *line, t_envs *envs)
{
	t_lexer_state	state;

	state.i = -1;
	state.j = 0;
	state.group = malloc(2 * sizeof(int));
	state.in_quotes = 0;
	state.quote_type = 0;
	state.start_quote = -1;
	state.end_quote = -1;
	state.in_qdollas = 0;
	state.y = 0;
	state.split_line = ft_calloc(4096 * 4, sizeof(char));
	while (line[++state.i])
	{
		handle_quotes(line, &state);
		if (handle_special_chars(line, &state) < 0)
			return (NULL);
		if (handle_spaces(line, &state) < 0)
			break ;
		if (handle_expansion(line, &state, envs) < 0)
			break ;
		if (handle_end_of_line(line, &state) < 0)
			break ;
	}
	return (state.split_line);
}
