/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_mem.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:05:46 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/27 14:14:42 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_envs(t_envs **envs)
{
	t_entry	*tmp;

	while ((*envs)->env->next)
	{
		tmp = (*envs)->env;
		(*envs)->env = (*envs)->env->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
	while ((*envs)->exp->next)
	{
		tmp = (*envs)->exp;
		(*envs)->exp = (*envs)->exp->next;
		free(tmp->name);
		free(tmp->value);
		free(tmp);
	}
}

void	free_entry(t_entry *entry)
{
	if (entry->prev)
		entry->prev->next = entry->next;
	if (entry->next)
		entry->next->prev = entry->prev;
	if (entry->name)
		free(entry->name);
	entry->name = NULL;
	if (entry->value)
		free(entry->value);
	entry->value = NULL;
	if (entry)
		free(entry);
	entry = NULL;
}

void	ft_entry_addb(t_entry **lst, t_entry *node)
{
	t_entry	*last;

	if (node == NULL)
		return ;
	last = lastentry(*lst);
	node->prev = last;
	if (last != NULL)
		last->next = node;
	else
		*lst = node;
}
