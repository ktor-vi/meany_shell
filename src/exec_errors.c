/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:08:00 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/27 14:09:00 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pipe_error(void)
{
	perror("pipe() error");
	exit(EXIT_FAILURE);
}

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
