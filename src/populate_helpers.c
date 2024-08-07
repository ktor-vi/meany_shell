/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate_helpers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:11:18 by vphilipp          #+#    #+#             */
/*   Updated: 2024/07/25 14:21:11 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>

int	redirect_handle(char **split_line, int j, int code)
{
	int		fd;
	char	*true_name;

	true_name = ft_strqtrim(ft_strdup(split_line[j + 1]));
	if (code == O_APPEND)
		fd = open(true_name, O_WRONLY | O_APPEND);
	else
		fd = open(true_name, O_WRONLY | O_TRUNC);
	if (fd < 0)
	{
		fd = open(true_name, O_CREAT, 0666);
		close(fd);
		if (code == O_APPEND)
			fd = open(true_name, O_WRONLY | O_APPEND);
		else
			fd = open(true_name, O_WRONLY | O_TRUNC);
	}
	free(true_name);
	return (fd);
}

void	assign_here_doc(t_command *h, char **split_line, int i)
{
	int	k;

	k = -1;
	h->eof = NULL;
	h->heredoc = 0;
	while (split_line[++k])
	{
		if (ft_equalstr(split_line[i + k], "<<") && ft_equalstr(split_line[i],
				"<<"))
		{
			h->heredoc = 1;
			h->eof = ft_strdup(split_line[i + 1]);
			break ;
		}
		else if (ft_equalstr(split_line[i + k], "<<")
			&& !ft_equalstr(split_line[i], "<<"))
		{
			h->heredoc = -1;
			break ;
		}
	}
}
