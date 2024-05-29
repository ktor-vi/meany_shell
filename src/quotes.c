/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 13:59:23 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/29 11:05:39 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	closed_quotes(char *line)
{
	int	i;
	int	type;

	i = get_firstq_pos(line);
	type = get_q_type(line, i);
	i++;
	if (!line[i])
		return (0);
	while (line[i])
	{
		if (line[i] == '"' && type == 2)
			return (1);
		else if (line[i] == 39 && type == 1)
			return (2);
		else
			i++;
	}
	return (0);
}

char	*simple_q(char *line, char *trimmed, int *type)
{
	if (*type == 0)
	{
		*type = 1;
		line++;
	}
	else if (*type == 1)
	{
		*type = 0;
		line++;
	}
	else
	{
		*trimmed = *line;
		line++;
		trimmed++;
	}
	return (trimmed);
}

char	*double_q(char *line, char *trimmed, int *type)
{
	if (*type == 0)
	{
		*type = 2;
		line++;
	}
	else if (*type == 2)
	{
		*type = 0;
		line++;
	}
	else
	{
		*trimmed = *line;
		line++;
		trimmed++;
	}
	return (trimmed);
}

char	*follow_thru(char *line, char *trimmed)
{
	*trimmed = *line;
	trimmed++;
	return (trimmed);
}

char	*ft_strqtrim(char *line)
{
	char	*trimmed;
	char	*start;
	int		*type;

	trimmed = malloc((ft_strlen(line) + 1) * sizeof(char));
	type = malloc(sizeof(int));
	*type = 0;
	start = trimmed;
	while (*line)
	{
		if (*line != 39 && *line != '"')
			trimmed = follow_thru(line, trimmed);
		else if (*line == 39)
			trimmed = simple_q(line, trimmed, type);
		else if (*line == '"')
			trimmed = double_q(line, trimmed, type);
		line++;
	}
	*trimmed = 0;
	return (start);
}
