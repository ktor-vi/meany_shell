/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 14:27:30 by randre            #+#    #+#             */
/*   Updated: 2024/05/06 15:21:20 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_arr(char **split_arr)
{
	int	i;

	i = 0;
	while (split_arr[i])
	{
		free(split_arr[i]);
		i++;
	}
	free(split_arr);
}

void	ft_simple_cmdsclear(t_simple_cmds **lst)
{
	t_simple_cmds	*tmp;
	t_lexer			*redirections_tmp;

	if (!*lst)
		return ;
	while (*lst)
	{
		tmp = (*lst)->next;
		redirections_tmp = (*lst)->redirections;
		//ft_lexerclear(&redirections_tmp);
		if ((*lst)->str)
			free_arr((*lst)->str);
		if ((*lst)->hd_file_name)
			free((*lst)->hd_file_name);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}

int	mini_init(t_minishell *minishell)
{
	minishell->simple_cmds = NULL;
	minishell->args = NULL;
	minishell->lexer_list = NULL;
	minishell->reset = false;
	minishell->pid = NULL;
	minishell->heredoc = false;
	return (1);
}

void	reset_minishell(t_minishell *minishell)
{
	ft_simple_cmdsclear(&minishell->simple_cmds);
	free(minishell->args);
	if (minishell->pid)
		free(minishell->pid);
	free_arr(minishell->paths);
	mini_init(minishell);
	minishell->reset = true;
}