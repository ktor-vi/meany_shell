/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:00:33 by vphilipp          #+#    #+#             */
/*   Updated: 2024/06/13 18:19:41 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	double_quotes_expand(char *line, t_lexer_state *st, t_envs *envs)
{
	int	i;

	i = 0;
	if (st->in_quotes == 1 && !st->in_qdollas && st->start_quote < st->i)
		st->split_line[st->j++] = ft_strndup(line, st->start_quote + 1, st->i
				- 1);
	st->split_line[st->j] = ft_expand(line, st, envs);
	if (st->split_line[st->j])
		st->j++;
	while (ft_isspace(line[st->i]))
		st->i++;
	while (st->in_quotes == 1 && !st->in_qdollas && line[st->i + i] != '$'
		&& line[st->i + i] != '"')
		i++;
	if (i)
		st->in_qdollas = 1;
	else if (line[st->i + i] == '"')
		st->in_qdollas = 0;
	if (i)
		st->split_line[st->j++] = ft_strndup(line, st->i, st->i + i - 1);
	st->y = st->i;
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
		lex_expand(line, state, envs);
		if (line[state->i] == 0)
			return (-1);
		while (ft_isspace(line[state->i]))
			state->i++;
		state->y = state->i;
		state->i--;
	}
	return (0);
}
