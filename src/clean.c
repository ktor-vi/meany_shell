/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:37:27 by randre            #+#    #+#             */
/*   Updated: 2024/06/13 18:20:17 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clean_arg_s(t_command *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->args_ct)
	{
		free(cmd->arg[i]);
	}
	free(cmd->arg);
}

static void	clean_command(t_command *cmd)
{
	if (cmd->eof)
	{
		free(cmd->eof);
		cmd->eof = NULL;
	}
	free(cmd->path);
	cmd->path = NULL;
	if (cmd->fd != STDOUT_FILENO)
		close(cmd->fd);
	clean_arg_s(cmd);
}

void	clean_minishell(t_minishell *minishell)
{
	t_command	*temp_cmd;

	if (minishell->cmd != NULL)
	{
		while (minishell->cmd)
		{
			temp_cmd = minishell->cmd->next;
			clean_command(minishell->cmd);
			free(minishell->cmd);
			minishell->cmd = temp_cmd;
		}
	}
	free(minishell);
	minishell = NULL;
}
