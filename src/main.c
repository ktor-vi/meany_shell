/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/01/08 16:20:47 by randre           ###   ########.fr       */
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
		if (!ft_strcmp(line, ""))
		{
			split_line = ft_split(line, ' ');
			if (ft_strcmp(split_line[0], "exit")
			check_command(split_line);
			while(split_line[++i])
				free(split_line[i]);
			free(split_line);
		}
		free(line);
	}
	return (0);
}
