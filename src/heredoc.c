/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:10:42 by vphilipp          #+#    #+#             */
/*   Updated: 2024/07/25 14:19:58 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

void	here_doc(t_command *h, t_envs *envs, int *st)
{
	char	*line;
	int		here_pfds[2];

	create_pipe(here_pfds);
	while (1)
	{
		write(st[1], "> ", 2);
		line = get_next_line(st[0]);
		if (line == NULL)
			break ;
		if (ft_strncmp(line, h->eof, ft_strlen(h->eof)) == 0
			&& ft_strlen(line) == ft_strlen(h->eof) + 1)
			break ;
		write(here_pfds[1], line, ft_strlen(line));
		free(line);
	}
	if (line)
		free(line);
	close(here_pfds[1]);
	dup2(here_pfds[0], STDIN_FILENO);
	close(here_pfds[0]);
	if (!pre_heredoc(h))
		handle_execve(h, envs);
}
