/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:59:02 by vphilipp          #+#    #+#             */
/*   Updated: 2024/09/19 11:36:34 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_ints(t_minishell *minishell)
{
	minishell->cmd = NULL;
	minishell->pos = 0;
	minishell->cmd_pos = 0;
	minishell->failed = 0;
	minishell->fd = STDOUT_FILENO;
}

void	finish_pop(t_minishell *m, t_envs *envs)
{
	post_parse(m);
	if (!m->cmd)
		return ;
	set_paths(m->cmd, envs);
}

int	redir_cond(char **split_line, t_minishell *m)
{
	if (ft_strcmp(split_line[m->pos], "<<") == 0
		|| ft_equalstr(split_line[m->pos], ">") || ft_strcmp(split_line[m->pos],
			">>") == 0)
		return (1);
	else
		return (0);
}

void	redir_cases(char **split_line, t_minishell *m)
{
	m->fd = -1;
	while (split_line[m->pos] && (ft_equalstr(split_line[m->pos], ">")
			|| ft_equalstr(split_line[m->pos], ">>")))
	{
		if (access(split_line[m->pos + 1], F_OK) == 0 && access(split_line[m->pos
					+ 1], W_OK) < 0)
		{
			ft_printf(1, "%s : permission denied\n", split_line[m->pos + 1]);
			g_exit_codes = 1;
			m->failed = 1;
			return ;
		}
		if(m->pos == 0)
			m->failed = 1;
		if (ft_equalstr(split_line[m->pos], ">"))
			m->fd = redirect_handle(split_line, m->pos, O_WRONLY);
		else if (ft_equalstr(split_line[m->pos], ">>"))
			m->fd = redirect_handle(split_line, m->pos, O_APPEND);
		m->pos += 2;
	}
	if (ft_strcmp(split_line[m->pos], "<<") == 0)
		m->pos += 2;
}

t_minishell	*populate_cmds(char **split_line, t_envs *envs)
{
	t_minishell	*m;

	m = ft_calloc(1, sizeof(t_minishell));
	init_ints(m);
	while (split_line[m->pos] != NULL)
	{
		while (split_line[m->pos] && !is_tok(split_line, m->pos))
			m->pos++;
		if (redir_cond(split_line, m))
			redir_cases(split_line, m);
		if (!split_line)
			return (m);
		if (ft_strcmp(split_line[m->pos], "|") == 0)
		{
			m->fd = STDOUT_FILENO;
			ft_cmd_addb(&m, build_command(split_line, m->cmd_pos, m->fd));
			m->cmd_pos = m->pos + 1;
			m->pos++;
			continue ;
		}
		ft_cmd_addb(&m, build_command(split_line, m->cmd_pos, m->fd));
		m->pos += 2;
	}
	finish_pop(m, envs);
	return (m);
}
