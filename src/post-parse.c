/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post-parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:17:57 by vphilipp          #+#    #+#             */
/*   Updated: 2024/06/13 18:19:54 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

int	calc_offset(char **split_line, int pos)
{
	int	i;

	i = 0;
	while (split_line[i + pos] != NULL && !ft_equalstr(split_line[i + pos],
			"<<") && !ft_equalstr(split_line[i + pos], "|"))
	{
		if (ft_equalstr(split_line[pos + i], ">") || ft_equalstr(split_line[pos
					+ i], ">>") || ft_equalstr(split_line[pos + i], "<"))
		{
			i++;
		}
		break ;
		i++;
	}
	return (i);
}

t_command	*alloc_command(char **split_line, int pos, int fd)
{
	t_command	*new;
	int			i;
	int			size;

	i = 0;
	new = malloc(sizeof(t_command));
	new->fd = fd;
	while (split_line[i + pos] != NULL && !ft_equalstr(split_line[i + pos],
			"<<") && !ft_equalstr(split_line[i + pos], "|"))
		i++;
	new->args_ct = i + 1;
	new->arg = ft_calloc(new->args_ct, sizeof(t_args *));
	new->args = ft_calloc((new->args_ct), sizeof(char *));
	new->to_pipe = 0;
	new->eof = NULL;
	new->heredoc = 0;
	return (new);
}

t_command	*build_command(char **split_line, int pos, int fd)
{
	t_command	*new;
	int			i;

	i = 0;
	new = alloc_command(split_line, pos, fd);
	while (split_line[i + pos] && !is_endtok(split_line, pos + i))
	{
		if (is_reditok(split_line, pos + i))
			break ;
		new->arg[i] = ft_calloc(1, sizeof(t_args));
		new->arg[i]->in_quotes = closed_quotes(split_line[pos + i]);
		if (new->arg[i]->in_quotes)
			new->args[i] = ft_strqtrim(split_line[pos + i]);
		else
			new->args[i] = ft_strdup(split_line[pos + i]);
		i++;
	}
	if (ft_equalstr(split_line[i + pos], "<<") && split_line[i + pos + 1])
		assign_here_doc(new, split_line, i + pos);
	if (split_line[i + pos] && ft_equalstr(split_line[i + pos], "|"))
		new->to_pipe = 1;
	return (new);
}

void	post_parse(t_minishell *minishell, t_envs *envs)
{
	int			i;
	t_minishell	*tmp;
	t_command	*it;
	t_command	*next;

	tmp = ft_calloc(1, sizeof(t_minishell));
	it = minishell->cmd;
	i = 0;
	while (it)
	{
		next = it->next;
		if (it->heredoc && !pre_pipe(it))
			ft_cmd_addb(&tmp, it);
		else if (it->to_pipe && !pre_heredoc(it))
			ft_cmd_addb(&tmp, it);
		else if (!pre_heredoc(it))
			ft_cmd_addb(&tmp, it);
		it = next;
	}
	minishell->cmd = tmp->cmd;
	free(tmp);
}
