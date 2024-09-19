/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_uns_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:16:58 by vphilipp          #+#    #+#             */
/*   Updated: 2024/09/19 10:28:00 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
		ft_printf(2, "export: `%s': not a valid identifier\n", entry);
		g_exit_codes = 1;
		return (NULL);
	}
	while (var[i])
	{
		if (var[i] == '/' || var[i] == '%')
		{
			ft_printf(2, "export: `%s': not a valid identifier\n", entry);
			g_exit_codes = 1;
			return (NULL);
		}
		i++;
	}
	return (var);
}

static char	*calc_append_varname(t_entry *entry, char *var_name, char *var,
		int eq_pos)
{
	char	*value;
	char	*trim;
	char	*eq;
	char	*sub;
	char	*new_varname;

	sub = ft_substr(var, eq_pos + 1, ft_strlen(var) - eq_pos);
	trim = ft_strtrim(sub, "\"'");
	value = ft_strjoin(entry->value, trim);
	eq = ft_strjoin(var_name, "=");
	new_varname = ft_strjoin(eq, value);
	free(sub);
	free(value);
	free(eq);
	free(trim);
	free(var_name);
	return (new_varname);
}

void	append_value(t_envs *envs, char *var, int eq_pos)
{
	t_entry	*entry;
	char	*var_name;
	char	*new_varname;

	new_varname = NULL;
	var_name = ft_substr(var, 0, eq_pos - 1);
	entry = find_entry(envs->env, var_name);
	if (!entry)
		ft_entry_addb(&envs->env, newentry(var));
	else
	{
		new_varname = calc_append_varname(entry, var_name, var, eq_pos);
		ft_entry_addb(&envs->env, newentry(new_varname));
	}
	if (!entry)
		ft_entry_addb(&envs->exp, newentry(var));
	else
		ft_entry_addb(&envs->env, newentry(new_varname));
	free(new_varname);
}
