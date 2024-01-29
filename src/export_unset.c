#include "../includes/minishell.h"

static t_entry	*only_exp_entry(char *var)
{
	t_entry	*new;
	size_t	eq_pos;

	new = malloc(sizeof(t_entry));
	if (!new)
		return (NULL);
	new->name = ft_strdup(var);
	new->value = NULL;
	new->next = NULL;
	return (new);
}
t_entry	*find_entryprev(t_entry *lst, char *to_find)
{
	while (lst->next)
	{
		if (ft_equalstr(lst->next->name, to_find))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	export_cmd(t_envs *envs, char *var)
{
	t_entry	*new;
	int		eq_pos;

	new = malloc(sizeof(t_entry));
	eq_pos = getchindex(var, '=');
	new->next = NULL;
	if (!new || !envs || !var)
		return ;
	if (eq_pos < 0)
	{
		envs->exp_ct++;
		ft_entry_addb(&envs->exp, only_exp_entry(var));
	}
	else
	{
		ft_entry_addb(&envs->env, newentry(var));
		ft_entry_addb(&envs->exp, newentry(var));
		envs->exp_ct++;
		envs->env_ct++;
		sort_alpha_ll(&envs->exp, envs->exp_ct);
	}
}

void	unset_cmd(t_envs *envs, char *var)
{

	t_entry *env_prev;
	t_entry *exp_prev;
	t_entry *tmp;

	env_prev = find_entryprev(envs->env, var);
	exp_prev = find_entryprev(envs->exp, var);
	if (getchindex(var, '=') > 0)
		printf("unset: `%s': not a valid identifier\n", var);
	else
	{
		if(env_prev)
		{
			tmp = env_prev->next;
			env_prev->next = env_prev->next->next;
			free_entry(tmp);
		}
		if(exp_prev)
		{
			tmp = exp_prev->next;
			exp_prev->next = exp_prev->next->next;
			free_entry(tmp);
		}
	}
}
