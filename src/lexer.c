/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 12:45:22 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/30 17:30:34 by vphilipp         ###   ########.fr       */
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
	i = -1;
	len = end - start;
	s = malloc((len + 1) * sizeof(char));
	if (!s)
		return (NULL);
	while (++i < len)
		s[i] = str[start + i];
	s[len] = '\0';
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

void	handle_quotes(char *line, t_lexer_state *st)
{
	if ((line[st->i] == '"' || line[st->i] == 39))
	{
		if (st->in_quotes == 1 && line[st->i] == '"' && st->quote_type == 1)
			st->end_quote = st->i;
		else if (st->in_quotes == 0 && line[st->i] == '"'
			&& st->quote_type == 0)
			st->start_quote = st->i;
		else if (st->in_quotes == 2 && line[st->i] == 39 && st->quote_type == 2)
			st->end_quote = st->i;
		else if (st->in_quotes == 0 && line[st->i] == 39 && st->quote_type == 0)
			st->start_quote = st->i;
		verify_quotes(line, st->i, &st->in_quotes);
		if (st->end_quote == -1 && st->start_quote >= 0)
		{
			st->quote_type = st->in_quotes;
			st->group[0] = st->j;
		}
		else if (st->end_quote > 0 && line[st->i] == st->end_quote)
		{
			st->quote_type = 0;
			st->group[1] = st->j;
		}
	}
}

int	handle_end_of_line(char *line, t_lexer_state *state)
{
	if (line[state->i + 1] == 0)
	{
		state->split_line[state->j] = ft_strndup(line, state->y, state->i + 1);
		state->split_line[state->j + 1] = NULL;
		return (-1);
	}
	return (0);
}

char	**lexer(char *line, t_envs *envs)
{
	t_lexer_state	state;

	init_state(&state);
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
	free(state.group);
	return (state.split_line);
}
