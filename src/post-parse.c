/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post-parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 11:17:57 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/22 11:20:44 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>

int	pre_heredoc(t_command *cmd)
{
	t_command	*it;
	t_command	*next;

	it = cmd->next;
	while (it)
	{
		next = it->next;
		if (it->heredoc)
			return (1);
		it = next;
	}
	return (0);
}

int	pre_pipe(t_command *cmd)
{
	t_command	*it;
	t_command	*next;

	it = cmd;
	while (it)
	{
		next = it->next;
		if (it->to_pipe)
			return (1);
		it = next;
	}
	return (0);
}


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
	new->arg = malloc(new->args_ct * sizeof(t_args *));
	new->args = ft_calloc((new->args_ct), sizeof(char *));
	new->to_pipe = 0;
	new->heredoc = 0;
	new->next_tok = NULL;
	return (new);
}
t_command	*build_command(char **split_line, int pos, int fd)
{
	t_command	*new;
	int			i;

	i = 0;
	new = alloc_command(split_line, pos, fd);
	while (split_line[i + pos] != NULL && !ft_equalstr(split_line[i + pos],
			"<<") && !ft_equalstr(split_line[i + pos], "|"))
	{
		if (ft_equalstr(split_line[pos + i], ">") || ft_equalstr(split_line[pos
				+ i], ">>") || ft_equalstr(split_line[pos + i], "<"))
			break ;
		new->args[i] = ft_strdup(split_line[i + pos]);
		i++;
	}
	if (ft_equalstr(split_line[i + pos], "<<") && split_line[i + pos + 1])
	{
		new->eof = ft_strdup(split_line[i + pos + 1]);
		// ft_printf(1, "eof : %s\n", split_line[i + pos + 1]);
		new->heredoc = 1;
	}
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
		ft_printf(1, "%d - cmd : %s - pipe : %d - hd : %d pre | %d -- pre << %d\n",i++, it->args[0], it->to_pipe, it->heredoc,  pre_pipe(it) ,pre_heredoc(it));
		next = it->next;
		if (it->heredoc && !pre_pipe(it))
			ft_cmd_addb(&tmp, it);
		else if(it->to_pipe && !pre_heredoc(it))
			ft_cmd_addb(&tmp, it);
		else if (pre_heredoc(it)) // FREEE
			ft_printf(1, "skipped : %s\n", it->args[0]);
		it = next;
	}
	minishell->cmd = tmp->cmd;
	free(tmp);
}


int	is_tok(char **split_line, int pos)
{
	if ((ft_equalstr(split_line[pos], ">>")
			|| ft_equalstr(split_line[pos], "<") || ft_equalstr(split_line[pos],
				"<<") || ft_equalstr(split_line[pos], ">")
			|| ft_equalstr(split_line[pos], "|")))
		return (1);
	else
		return (0);
}

int	is_reditok(char **split_line, int pos)
{
	if ((ft_equalstr(split_line[pos], ">>")
			|| ft_equalstr(split_line[pos], "<") || ft_equalstr(split_line[pos], ">")
			))
		return (1);
	else
		return (0);
}

t_minishell	*populate_cmds(char **split_line, t_envs *envs)
{
	int			pos;
	int			fd;
	t_minishell	*minishell;
	t_command	*cmd;
	int			cmd_pos;

	pos = 0;
	cmd_pos = 0;
	fd = STDOUT_FILENO;
	minishell = malloc(sizeof(t_minishell));
	minishell->cmd = NULL;
	while (split_line[pos] != NULL)
	{
		while (split_line[pos] && !is_tok(split_line, pos))
			pos++;
		if (ft_strcmp(split_line[pos], "<<") == 0)
			pos += 2;
		if (ft_strcmp(split_line[pos], "|") == 0)
		{
			fd = STDOUT_FILENO;
			ft_cmd_addb(&minishell, build_command(split_line, cmd_pos, fd));
			// ft_printf(1, "split_line[%d]: %s - net : %s\n", pos, split_line[pos], split_line[cmd_pos]);
			cmd_pos = pos + 1;
			pos++;
			continue ;
		}
		if (ft_equalstr(split_line[pos], ">"))
			fd = redirect_handle(split_line, pos);
		ft_cmd_addb(&minishell, build_command(split_line, cmd_pos, fd));
		pos += 2;
	}
	post_parse(minishell, envs);
	set_paths(minishell->cmd, envs);
	return (minishell);
}
