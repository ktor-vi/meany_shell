/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:40:05 by randre            #+#    #+#             */
/*   Updated: 2024/01/18 11:00:56 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_command(char **split_line)
{
	if (chdir(split_line[1]) != 0)
	{
		write(2, "cd: no such file or directory: ", 32);	
		write(2, split_line[1], ft_strlen(split_line[1]));
		write(2, "\n", 1);
	}
}