/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_envs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:34:52 by randre            #+#    #+#             */
/*   Updated: 2024/02/04 20:48:04 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_entry	*shlvl(void)
{
	t_entry	*shlvl;

	shlvl = malloc(sizeof(t_entry));
	if (!shlvl)
		return (NULL);
	shlvl->name = ft_strdup("SHLVL");
	shlvl->value = ft_strdup("1");
	shlvl->prev = NULL;
	shlvl->next = NULL;
	return (shlvl);
}

static t_entry	*pwd(void)
{
	char	*str;
	t_entry	*pwd;

	pwd = malloc(sizeof(t_entry));
	str = malloc(2048 * sizeof(char));
	if (!str || !pwd)
		return (NULL);
	getcwd(str, 2048);
	pwd->name = ft_strdup("PWD");
	pwd->value = ft_strdup(str);
	pwd->prev = NULL;
	pwd->next = NULL;
	free(str);
	return (pwd);
}

static t_envs	*empty_envs(t_envs *envs)
{
	ft_entry_addb(&envs->env, pwd());
	ft_entry_addb(&envs->exp, pwd());
	ft_entry_addb(&envs->env, shlvl());
	ft_entry_addb(&envs->exp, shlvl());
	return (envs);
}
t_envs	*build_envs(char **envp)
{
	t_envs	*envs;
	int		i;

	i = 0;
	envs = malloc(sizeof(t_envs));
	envs->env = NULL;
	envs->exp = NULL;
	if (!envp[i])
		return (empty_envs(envs));
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
