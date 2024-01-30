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
	if (!lst | !to_find)
		return (NULL);
	while (lst->next)
	{
		if (ft_equalstr(lst->next->name, to_find))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void	append_value(t_envs *envs, char *var, int eq_pos)
{
	t_entry	*entry;
	char	*var_name;
	char	*value;

	var_name = ft_substr(var, 0, eq_pos - 1);
	entry = find_entryprev(envs->env, var_name);
	if (!entry)
		ft_entry_addb(&envs->env, newentry(var));
	else
	{
		entry = entry->next;
		value = ft_strjoin(entry->value, ft_strtrim(ft_strtrim(ft_substr(var,
						eq_pos + 1, ft_strlen(var) - eq_pos), "\""), "'"));
		entry->value = value;
		entry = find_entryprev(envs->exp, var_name);
	}
	if (!entry)
		ft_entry_addb(&envs->exp, newentry(var));
	else
	{
		entry = entry->next;
		entry->value = value;
	}
}

void	export_cmd(t_envs *envs, char *var)
{
	int		eq_pos;
	char	*var_name;

	eq_pos = getchindex(var, '=');
	var_name = ft_substr(var, 0, eq_pos);
	if (!var)
		return ;
	if (!find_entryprev(envs->exp, var_name))
		envs->exp_ct++;
	if (!find_entryprev(envs->env, var_name))
		envs->env_ct++;
	if (var[eq_pos - 1] == '+' && eq_pos > 0)
		append_value(envs, var, eq_pos);
	else if (eq_pos < 0 && find_entryprev(envs->exp, var_name) == NULL)
		ft_entry_addb(&envs->exp, only_exp_entry(var));
	else if (eq_pos > 0)
	{
		if (find_entryprev(envs->exp, var_name) && var[eq_pos - 1] != '+')
			free_entry(find_entryprev(envs->exp, var_name));
		if (find_entryprev(envs->env, var_name) && var[eq_pos - 1] != '+')
			free_entry(find_entryprev(envs->env, var_name));
		ft_entry_addb(&envs->env, newentry(var));
		ft_entry_addb(&envs->exp, newentry(var));
	}
		sort_alpha_ll(&envs->exp, envs->exp_ct);
}

void	unset_cmd(t_envs *envs, char *var)
{
	t_entry	*env_prev;
	t_entry	*exp_prev;

	env_prev = find_entryprev(envs->env, var);
	exp_prev = find_entryprev(envs->exp, var);
	if (getchindex(var, '=') > 0)
		printf("unset: `%s': not a valid identifier\n", var);
	else
	{
		if (env_prev)
			free_entry(env_prev);
		if (exp_prev)
			free_entry(exp_prev);
	}
}
