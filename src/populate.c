/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   populate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 18:59:02 by vphilipp          #+#    #+#             */
/*   Updated: 2024/06/18 14:49:59 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_ints(t_minishell *minishell)
{
	minishell->cmd = NULL;
	minishell->pos = 0;
	minishell->cmd_pos = 0;
	minishell->fd = STDOUT_FILENO;
}

void	finish_pop(t_minishell *m, t_envs *envs)
{
	post_parse(m);
	set_paths(m->cmd, envs);
}

int	redir_cond(char **split_line, t_minishell *m)
{
	if (ft_strcmp(split_line[m->pos], "<<") == 0
		|| ft_equalstr(split_line[m->pos], ">"))
		return (1);
	else
		return (0);
}

void	redir_cases(char **split_line, t_minishell *m)
{
	if (ft_equalstr(split_line[m->pos], ">"))
		m->fd = redirect_handle(split_line, m->pos, O_WRONLY);
	else if (ft_equalstr(split_line[m->pos], ">>"))
		m->fd = redirect_handle(split_line, m->pos, O_APPEND);
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
