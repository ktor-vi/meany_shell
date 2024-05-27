/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:46:42 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/27 14:16:20 by vphilipp         ###   ########.fr       */
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


int	export_cases(t_envs *envs, char *var)
{
	int		eq_pos;
	char	*var_name;

	eq_pos = getchindex(var, '=');
	var_name = validate_var(ft_substr(var, 0, eq_pos), var);
	if (!var_name)
		return (1);
	if (eq_pos > 0 && var[eq_pos - 1] == '+')
		append_value(envs, var, eq_pos);
	else if (eq_pos < 0 && find_entry(envs->exp, var_name) == NULL)
		ft_entry_addb(&envs->exp, only_exp_entry(var));
	else if (eq_pos > 0)
	{
		if (find_entry(envs->exp, var_name) && var[eq_pos - 1] != '+')
			free_entry(find_entry(envs->exp, var_name));
		if (find_entry(envs->env, var_name) && var[eq_pos - 1] != '+')
			free_entry(find_entry(envs->env, var_name));
		ft_entry_addb(&envs->env, newentry(var));
		ft_entry_addb(&envs->exp, newentry(var));
	}
	free(var_name);
	var_name = NULL;
	return (0);
}

void	export_cmd(t_envs *envs, char **vars)
{
	int	i;

	i = 0;
	if (!vars)
		return ;
	while (vars[++i])
	{
		if (export_cases(envs, vars[i]))
			return;
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
}
