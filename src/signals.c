/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:15:11 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/29 12:44:42 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_sigint2(int sig)
{
	if (sig == SIGINT)
	{
		ft_putendl_fd("", 1);
	}
}

void	handle_sigquit(int sig)
{
	if (sig == SIGQUIT)
	{
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
}
