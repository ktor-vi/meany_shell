/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:49:03 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/22 11:17:11 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printenv(t_entry *env, t_command *cmd)
{
	t_entry	*tmp;

	if (!env)
		return ;
	tmp = env;
	while (tmp != NULL)
	{
		ft_printf(cmd->fd, "%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
	ft_printf(cmd->fd, "\n");
}

void	printexport(t_entry *exp, t_command *cmd)
{
	t_entry	*tmp;

	if (!exp)
		return ;
	tmp = exp;
	while (tmp != NULL)
	{
		if (tmp->value)
			ft_printf(cmd->fd, "declare -x %s=\"%s\"\n", tmp->name, tmp->value);
		else
			ft_printf(cmd->fd, "declare -x %s\n", tmp->name);
		tmp = tmp->next;
	}
	ft_printf(cmd->fd, "\n");
}

void	printtab(char **exp)
{
	uint	i;

	i = 0;
	while (exp[i])
	{
		printf("%s\n", exp[i]);
		i++;
	}
	printf("\n");
}

int	ll_size(t_entry *env)
{
	int	ct;

	ct = 0;
	while (env)
	{
		env = env->next;
		ct++;
	}
	return (ct);
}
char	**ll_to_tab(t_entry *env)
{
	char	**envp;
	int		i;
	char	*var;
	int		ct;

	if (!env)
		return (NULL);
	ct = ll_size(env);
	while (env)
	{
		env = env->next;
		ct++;
	}
	i = 0;
	envp = malloc(sizeof(char *) * ct + 1);
	while (env)
	{
		var = ft_strjoin(env->name, "=");
		var = ft_strjoin(var, env->value);
		envp[i] = var;
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
