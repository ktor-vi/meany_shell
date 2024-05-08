#include "../includes/minishell.h"

void free_envs(t_envs **envs)
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
	if(entry->next)
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
