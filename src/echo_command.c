/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:48:14 by randre            #+#    #+#             */
/*   Updated: 2024/01/08 15:12:04 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	echo_command(char **split_line)
{
	int	i;

	i = 0;
	if (!split_line[1])
		printf("\n");
	else if (ft_strcmp(split_line[1], "-n") && split_line[2])
	{
		i++;
		while (split_line[++i] && split_line[i + 1])
			printf("%s ", split_line[i]);
		printf("%s", split_line[i]);
	}
	else
	{
		if (ft_strcmp(split_line[1], "-n"))
			return ;
		while (split_line[++i] && split_line[i + 1])
			printf("%s ", split_line[i]);
		printf("%s\n", split_line[i]);
	}
}
