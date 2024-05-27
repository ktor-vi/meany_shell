/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_uns_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 14:16:58 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/27 14:17:02 by vphilipp         ###   ########.fr       */
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
		return (NULL);
	}
	while (var[i])
	{
		if (var[i] == '/')
		{
			ft_printf(2, "export: `%s': not a valid identifier\n", entry);
			return (NULL);
		}
		i++;
	}
	i = 0;
	while (var[i])
	{
		if (var[i] == '%')
		{
			ft_printf(2, "export: `%s': not a valid identifier\n", entry);
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
