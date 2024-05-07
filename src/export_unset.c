/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:46:42 by vphilipp          #+#    #+#             */
/*   Updated: 2024/02/04 20:46:52 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_entry	*only_exp_entry(char *var)
{
	t_entry	*new;

	new = malloc(sizeof(t_entry));
	if (!new || !var)
		return (NULL);
	new->name = ft_strdup(var);
	new->value = NULL;
	new->next = NULL;
	new->prev = NULL;
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

t_entry	*find_entry(t_entry *lst, char *to_find)
{
	if (!lst || !to_find || lst->name == NULL)
		return (NULL);
	while (lst)
	{
		if (ft_equalstr(lst->name, to_find))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

char	*validate_var(char *var, char *entry)
{
	int	i;

	i = 0;
	if (ft_isdigit(var[0]))
	{
		printf("export: `%s': not a valid identifier\n", entry);
		return (NULL);
	}
	while (var[i])
	{
		if (var[i] == '/')
		{
			printf("export: `%s': not a valid identifier\n", entry);
			return (NULL);
		}
		i++;
	}
	return (var);
}

void	append_value(t_envs *envs, char *var, int eq_pos)
{
	t_entry	*entry;
	char	*var_name;
	char	*value;

	var_name = ft_substr(var, 0, eq_pos - 1);
	entry = find_entry(envs->env, var_name);
	if (!entry)
		ft_entry_addb(&envs->env, newentry(var));
	else
	{
		value = ft_strjoin(entry->value, ft_strtrim(ft_strtrim(ft_substr(var,
						eq_pos + 1, ft_strlen(var) - eq_pos), "\""), "'"));
		entry->value = value;
		entry = find_entry(envs->exp, var_name);
	}
	if (!entry)
		ft_entry_addb(&envs->exp, newentry(var));
	else
		entry->value = value;
}

void	export_cmd(t_envs *envs, char **vars)
{
	int		eq_pos;
	char	*var_name;
	int		i;

	i = -1;
	if (!vars)
		return ;
	while (vars[++i])
	{
		eq_pos = getchindex(vars[i], '=');
		var_name = validate_var(ft_substr(vars[i], 0, eq_pos), vars[i]);
		if (!var_name)
			return ;
		if (eq_pos > 0 && vars[i][eq_pos - 1] == '+')
			append_value(envs, vars[i], eq_pos);
		else if (eq_pos < 0 && find_entry(envs->exp, var_name) == NULL)
			ft_entry_addb(&envs->exp, only_exp_entry(vars[i]));
		else if (eq_pos > 0)
		{
			if (find_entry(envs->exp, var_name) && vars[i][eq_pos - 1] != '+')
				free_entry(find_entry(envs->exp, var_name));
			if (find_entry(envs->env, var_name) && vars[i][eq_pos - 1] != '+')
				free_entry(find_entry(envs->env, var_name));
			ft_entry_addb(&envs->env, newentry(vars[i]));
			ft_entry_addb(&envs->exp, newentry(vars[i]));
		}
	}
	sort_alpha_ll(&envs->exp, ll_size(envs->exp));
}

void	unset_cmd(t_envs *envs, char *var)
{
	t_entry	*env;
	t_entry	*exp;

	env = find_entry(envs->env, var);
	exp = find_entry(envs->exp, var);
	if (!exp)
		return ;
	else if (getchindex(var, '=') > 0)
		printf("unset: `%s': not a valid identifier\n", var);
	else
	{
		if (env)
			free_entry(env);
		if (exp)
			free_entry(exp);
		envs->exp_ct--;
		if (envs->exp_ct == 0)
			envs->exp = NULL;
	}
	// printf("freed %p\n", exp->name);
}
