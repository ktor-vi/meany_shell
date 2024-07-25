/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:00:10 by vphilipp          #+#    #+#             */
/*   Updated: 2024/07/25 14:06:39 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	pre_heredoc(t_command *cmd)
{
	t_command	*it;
	t_command	*next;

	it = cmd->next;
	while (it)
	{
		next = it->next;
		if (it->heredoc)
			return (1);
		it = next;
	}
	return (0);
}

int	pre_pipe(t_command *cmd)
{
	t_command	*it;
	t_command	*next;

	it = cmd;
	while (it)
	{
		next = it->next;
		if (it->to_pipe)
			return (1);
		it = next;
	}
	return (0);
}

int	is_tok(char **split_line, int pos)
{
	if ((ft_equalstr(split_line[pos], ">>") || ft_equalstr(split_line[pos], "<")
			|| ft_strnstr(split_line[pos], "<<", 3)
			|| ft_equalstr(split_line[pos], ">") || ft_equalstr(split_line[pos],
				"|")))
		return (1);
	else
		return (0);
}

int	is_reditok(char **split_line, int pos)
{
	if ((ft_equalstr(split_line[pos], ">>") || ft_equalstr(split_line[pos], "<")
			|| ft_equalstr(split_line[pos], ">")))
		return (1);
	else
		return (0);
}

int	is_endtok(char **split_line, int pos)
{
	int	i;

	i = 0;
	if ((ft_equalstr(split_line[pos + i], "|") || ft_equalstr(split_line[pos
					+ i], "<<")))
		return (1);
	return (0);
}
