/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_command.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:40:05 by randre            #+#    #+#             */
/*   Updated: 2024/05/27 14:05:09 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd_command(char **split_line)
{
	char	*path;

	if (split_line[1])
	{
		if (chdir(split_line[1]) != 0)
		{
			write(2, "cd: no such file or directory: ", 32);
			write(2, split_line[1], ft_strlen(split_line[1]));
			write(2, "\n", 1);
		}
	}
	else
	{
		path = ft_strjoin("/Users/", getenv("USER"));
		chdir(path);
	}
}
