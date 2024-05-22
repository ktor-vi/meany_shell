/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   synthax_errors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 13:35:50 by randre            #+#    #+#             */
/*   Updated: 2024/05/22 11:18:04 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_tab(char **split_line)
{
	int	i;

	i = 0;
	while (split_line[i] != NULL)
	{
		free(split_line[i]);
		i++;
	}
	free(split_line);
	return ;
}

int	ft_error(int code, char **split_line, char *line, int i)
{
	if (code == 1)
	{
		ft_printf(STDERR_FILENO,
			"minishell: Parsing error: unexpected token '%c'\n", line[i]);
		ft_free_tab(split_line);
	}
	return (EXIT_FAILURE);
}