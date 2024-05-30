/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:00:33 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/30 16:04:10 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	post_special_increment(char *line, t_lexer_state *st)
{
	st->i++;
	while (ft_isspace(line[st->i]))
		st->i++;
	st->y = st->i;
	st->j++;
	st->i--;
}

int	handle_special_chars(char *line, t_lexer_state *st)
{
	if (ft_isspecial(line[st->i]) && !st->in_quotes)
	{
		if (!ft_isspace(line[st->i - 1]) && st->y < st->i)
			st->split_line[st->j++] = ft_strndup(line, st->y, st->i);
		if ((line[st->i + 1] == line[st->i]) && line[st->i] != '|')
		{
			if (ft_isspecial(line[st->i + 2]))
				return (ft_error(-1, st->split_line, line, st->i + 2));
			st->split_line[st->j] = ft_strndup(line, st->i, st->i + 2);
			st->i += 2;
		}
		else if (ft_isspecial(line[st->i + 1]))
			return (ft_error(-1, st->split_line, line, st->i + 1));
		else
		{
			st->split_line[st->j] = ft_strndup(line, st->i, st->i + 1);
			if (line[st->i] == '|' && line[st->i + 1] == '|')
				return (ft_error(-1, st->split_line, line, st->i + 1));
		}
		post_special_increment(line, st);
	}
	return (0);
}

int	handle_spaces(char *line, t_lexer_state *state)
{
	if (ft_isspace(line[state->i]) && !state->in_quotes)
	{
		if (state->y < state->i)
			state->split_line[state->j++] = ft_strndup(line, state->y,
					state->i);
		state->i++;
		while (ft_isspace(line[state->i]))
			state->i++;
		state->y = state->i;
		state->i--;
		if (line[state->i + 1] == 0)
			return (-1);
	}
	return (0);
}

void	double_quotes_expand(char *line, t_lexer_state *state, t_envs *envs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (state->in_quotes == 1 && !state->in_qdollas && j < state->i
		&& line[state->i - j - 1] != '"')
		j++;
	if (j)
		state->split_line[state->j++] = ft_strndup(line, state->i - j, state->i
				- 1);
	state->split_line[state->j] = ft_expand(line, state, envs);
	if (state->split_line[state->j])
		state->j++;
	while (ft_isspace(line[state->i]))
		state->i++;
	while (state->in_quotes == 1 && !state->in_qdollas && line[state->i
			+ i] != '$' && line[state->i + i] != '"')
		i++;
	if (i)
	{
		state->in_qdollas = 1;
		state->split_line[state->j++] = ft_strndup(line, state->i, state->i + i);
	}
	else if (line[state->i + i] == '"')
		state->in_qdollas = 0;
	state->y = state->i;
}

int	handle_expansion(char *line, t_lexer_state *state, t_envs *envs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (line[state->i] == '$' && state->in_quotes == 1)
		double_quotes_expand(line, state, envs);
	else if (line[state->i] == '$' && state->in_quotes != 2)
	{
		state->split_line[state->j++] = ft_expand(line, state, envs);
		if (line[state->i] == 0)
			return (-1);
		while (ft_isspace(line[state->i]))
			state->i++;
		state->y = state->i;
		state->i--;
	}
	return (0);
}
