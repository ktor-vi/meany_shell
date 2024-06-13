/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:26:48 by vphilipp          #+#    #+#             */
/*   Updated: 2024/06/13 14:58:13 by vphilipp         ###   ########.fr       */
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
