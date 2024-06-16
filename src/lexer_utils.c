/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:26:48 by vphilipp          #+#    #+#             */
/*   Updated: 2024/06/14 11:14:00 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ')
		return (1);
	else
		return (0);
}

int	ft_isspecial(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

void	init_state(t_lexer_state *state)
{
	state->i = -1;
	state->j = 0;
	state->in_quotes = 0;
	state->quote_type = 0;
	state->start_quote = -1;
	state->end_quote = -1;
	state->in_qdollas = 0;
	state->y = 0;
	state->group = malloc(2 * sizeof(int));
	state->split_line = ft_calloc(4096 * 4, sizeof(char));
}

void	lex_expand(char *line, t_lexer_state *state, t_envs *envs)
{
	char	**exp_split;
	char	*exp;
	int		i;

	i = -1;
	exp = ft_expand(line, state, envs);
	if (!exp)
		return;
	exp_split = lexer(exp, envs);
	while (exp_split[++i])
		state->split_line[state->j++] = ft_strdup(exp_split[i]);
	free_tab(exp_split);
	free(exp);
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
