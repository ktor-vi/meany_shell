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


void	ft_envclear(t_entry *lst)
{
	if (lst == NULL)
		return ;
	if (lst->next != NULL)
		ft_envclear(lst->next);
	free(lst->name);
	free(lst->value);
	free(lst);
	lst = NULL;
}





void	free_envs(t_envs *envs)
{
	ft_envclear(envs->env);
	ft_envclear(envs->exp);
	envs->exp = NULL;
	envs->env = NULL;
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
