/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:49:57 by randre            #+#    #+#             */
/*   Updated: 2024/06/06 13:20:21 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_command(t_command *cmd)
{
	char	*str;

	str = malloc(2048 * sizeof(char));
	if (!str)
		return ;
	getcwd(str, 2048);
	write(cmd->fd, str, ft_strlen(str));
	write(cmd->fd, "\n", 1);
	if (cmd->fd != 0)
		close(cmd->fd);
	g_exit_codes = 0;
	free(str);
}
