/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envs_commands.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:49:03 by vphilipp          #+#    #+#             */
/*   Updated: 2024/02/04 20:49:05 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	printenv(t_entry *env)
{
	if (!env)
		return ;
	while (env != NULL)
	{
		printf("%s=%s\n", env->name, env->value);
		env = env->next;
	}
	printf("\n");
}

void	printexport(t_entry *exp)
{
	if (!exp)
		return ;
	while (exp != NULL)
	{
		if (exp->value)
			printf("declare -x %s=\"%s\"\n", exp->name, exp->value);
		else
			printf("declare -x %s\n", exp->name);
		exp = exp->next;
	}
	printf("\n");
}

void	printtab(char **exp)
{
	uint	i;

	i = 0;
	while (exp != NULL)
	{
		while (exp[++i])
			printf("%s\n", exp[i]);
	}
	printf("\n");
}

int ll_size(t_entry *env)
{
	int ct;

	ct = 0;
	while(env)
	{
		env = env->next;
		ct++;
	}
 return ct;
}
char	**ll_to_tab(t_entry *env)
{
	char	**envp;
	int		i;
	char	*var;
	int ct;

	ct = ll_size(env);
	while(env)
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
