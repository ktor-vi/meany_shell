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
	write(1, "alloc_command\n", 14);
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
		new->args[i] = ft_strdup(split_line[i]);
		ft_printf(1, "| %d - newargs[i] : %s\n", i, new->args[i]);
		i++;
	}
	ft_printf(1, "| %d - nullcheck - : %s\n", i, new->args[i]);
	if (split_line[i + pos] && ft_equalstr(split_line[i + pos], "<<"))
	{
		new->eof = ft_strdup(split_line[i + pos + 1]);
		new->heredoc = 1;
	}
	if (split_line[i + pos] && ft_equalstr(split_line[i + pos], "|"))
		new->to_pipe = 1;
	return (new);
}
// t_command *build_list()
void	post_parse(t_minishell *minishell, t_envs *envs)
{
	int			i;
	int			lst_size;
	t_minishell	*tmp;

	tmp = ft_calloc(1, sizeof(t_minishell));
	i = 0;
	while (minishell->cmd)
	{
		if (minishell->cmd->heredoc)
		{
			if (minishell->cmd->to_pipe)
				minishell->cmd->fd = STDOUT_FILENO;
			ft_cmd_addb(&tmp, minishell->cmd);
			minishell->cmd = minishell->cmd->next;
			continue ;
		}
		ft_cmd_addb(&tmp, minishell->cmd);
		ft_printf(1, "added to true cmd list: %s\n", minishell->cmd->args[0]);
		minishell->cmd = minishell->cmd->next;
	}
	minishell->cmd = tmp->cmd;
	free(tmp);
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
		while (split_line[pos] && !ft_equalstr(split_line[pos], "|")
			&& !ft_equalstr(split_line[pos], ">")
			&& !ft_equalstr(split_line[pos], ">>")
			&& !ft_equalstr(split_line[pos], "<")
			&& !ft_equalstr(split_line[pos], "<<"))
			pos++;
		if (ft_strcmp(split_line[pos], "|") == 0)
			fd = STDOUT_FILENO;
		if (ft_equalstr(split_line[pos], ">"))
			fd = redirect_handle(split_line, pos);
		// if(ft_equalstr(split_line[j], "<<"))
		// 	assign_here_doc(new_command(split_line, envs, j, j + 1, fd),
		// 		split_line, j);
		ft_printf(1, "cmd: %s\n", split_line[cmd_pos]);
		ft_cmd_addb(&minishell, build_command(split_line, cmd_pos, fd));
		pos++;
		cmd_pos = pos;
	}
	post_parse(minishell, envs);
	ft_printf(1, "post-parse\n");
	set_paths(minishell->cmd, envs);
	write(1, "Populated\n", 10);
	return (minishell);
}
