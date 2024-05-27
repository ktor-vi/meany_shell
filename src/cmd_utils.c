/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:05:35 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/27 14:05:39 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_command	*lastcmd(t_command *lst)
{
	t_command	*ptr;

	ptr = lst;
	if (ptr == NULL)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	ft_cmd_addb(t_minishell **mini, t_command *node)
{
	t_command	*last;

	if (node == NULL)
		return ;
	node->next = NULL;
	node->prev = NULL;
	last = lastcmd((*mini)->cmd);
	node->prev = last;
	if (last != NULL)
		last->next = node;
	else
		(*mini)->cmd = node;
}

void	print_all_cmd(t_minishell *minishell)
{
	t_command	*h;
	int			j;
	int			i;

	j = 0;
	i = 0;
	h = minishell->cmd;
	while (h)
	{
		printf("Command %d : \n Path : %s, to pipe : %d - end %d\n", i, h->path,
			h->to_pipe, h->end);
		while ((h->args)[j])
		{
			printf("%d -- %s\n", j, (h->args)[j]);
			j++;
		}
		j = 0;
		h = h->next;
	}
}
