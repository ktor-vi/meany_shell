/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/01/08 15:06:16 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(void)
{
	char	*line;
	char	**split_line;
	int		i;

	while (1)
	{
		i = -1;
		line = readline("$ ");
		split_line = ft_split(line, ' ');
		if (!split_line)
		{
			split_line = malloc(1 * sizeof(char *));
			split_line[0] = line;
		}
		check_command(split_line);
		while(split_line[++i])
			free(split_line[i]);
		free(split_line);
		free(line);
	}
	return (0);
}