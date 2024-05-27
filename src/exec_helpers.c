/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_helpers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 14:17:43 by ktorvi            #+#    #+#             */
/*   Updated: 2024/05/27 14:13:03 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	handle_dup2(int oldfd, int newfd)
{
	if (oldfd != newfd && dup2(oldfd, newfd) == -1)
		dup2in_error();
}

void	handle_execve(t_command *h, t_envs *envs)
{
	execve(h->path, h->args, ll_to_tab(envs->env));
	if (errno == EFAULT)
		ft_printf(STDERR_FILENO, "%s: command not found\n", h->args[0]);
	else
		perror("execve failed");
}
