/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:15:11 by vphilipp          #+#    #+#             */
/*   Updated: 2024/09/10 14:46:40 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <signal.h>
#include <unistd.h>

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		ft_printf(STDOUT_FILENO, "\n");
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
		ft_printf(STDOUT_FILENO, "Quit: 3\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	set_signals_during_cmd(void)
{
	signal(SIGQUIT, handle_sigquit);
}

void	reset_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
