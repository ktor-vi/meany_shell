/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:05:44 by vphilipp          #+#    #+#             */
/*   Updated: 2024/06/18 14:51:30 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_firstq_pos(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '"' && line[i] != 39 && line[i])
		i++;
	if (!line[i])
		return (0);
	return (i);
}

int	get_q_type(char *line, int pos)
{
	int	type;

	if (line[pos] == 0)
		return (0);
	if (line[pos] == '"')
		type = 2;
	else if (line[pos] == 39)
		type = 1;
	else
		type = 0;
	return (type);
}
