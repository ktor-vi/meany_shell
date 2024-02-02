/* ************************************************************************** */ /*                                                                            */ /*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:34:52 by randre            #+#    #+#             */
/*   Updated: 2024/01/18 10:36:15 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_envs	*build_envs(char **envp)
{
	t_envs	*envs;
	int		i;

	i = 0;
	envs = malloc(sizeof(t_envs));
	envs->env = NULL;
	envs->exp = NULL;
	if (!envp)
	{
		envs->exp_ct = 0;
		return (envs);
	}
	while (envp[i])
	{
		ft_entry_addb(&envs->env, newentry(envp[i]));
		ft_entry_addb(&envs->exp, newentry(envp[i]));
		i++;
	}
	sort_alpha_ll(&envs->exp, i);
	envs->env_ct = i;
	envs->exp_ct = i;
	return (envs);
}

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
	if (entry->name)
		free(entry->name);
	entry->name = NULL;
	if(entry->value)
		free(entry->value);
	entry->value = NULL;
	if (entry)
		free(entry);
	entry = NULL;
}

