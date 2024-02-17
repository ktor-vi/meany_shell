/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktorvi <ktorvi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:17:43 by ktorvi            #+#    #+#             */
/*   Updated: 2024/02/17 14:17:44 by ktorvi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup2in_error(void)
{
	perror("dup2 for STDIN_FILENO failed");
	exit(EXIT_FAILURE);
}

void	dup2out_error(void)
{
	perror("dup2 for STDOUT_FILENO failed");
	exit(EXIT_FAILURE);
}

void	forkfail_error(void)
{
	perror("fork failed");
	exit(EXIT_FAILURE);
}

void	create_pipe(int pfds[2])
{
	if (pipe(pfds) == -1)
	{
		perror("pipe creation failed");
		exit(EXIT_FAILURE);
	}
}

void	parent_process(int prev_pipe, int pfds[2], t_command **h)
{
	close(pfds[1]);
	close(prev_pipe);
	*h = (*h)->next;
}
