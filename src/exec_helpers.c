/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:17:43 by ktorvi            #+#    #+#             */
/*   Updated: 2024/02/20 11:51:24 by vphilipp         ###   ########.fr       */
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

void	parent_process(int prev_pipe, int pfds[2])
{
	close(pfds[1]);
	if (prev_pipe != STDIN_FILENO)
		close(prev_pipe);
}
