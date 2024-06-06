/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 13:37:27 by randre            #+#    #+#             */
/*   Updated: 2024/06/06 14:41:53 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	clean_command_sequel(t_command *cmd)
{
	int	i;

	i = -1;
	/*if (cmd->arg)
	{
		while (cmd->arg[++i])
		{
			free(cmd->arg[i]);
		}
	}*/
}

static void	clean_command(t_command *cmd)
{
	int	i;

	i = -1;
	if (cmd->eof)
	{
		free(cmd->eof);
		cmd->eof = NULL;
	}
	if (cmd->path)
	{
		free(cmd->path);
		cmd->path = NULL;
	}
	if (cmd->args)
	{
		while (cmd->args[++i])
			free(cmd->args[i]);
		free(cmd->args);
	}
	clean_command_sequel(cmd);
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
}