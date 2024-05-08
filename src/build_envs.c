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

static void	oldpwd(char **envp, t_envs *envs)
{
	t_entry	*oldpwd;
	int		k;

	k = -1;
	oldpwd = malloc(sizeof(t_entry));
	if (!oldpwd)
		return ;
	oldpwd->name = ft_strdup("OLDPWD");
	oldpwd->value = NULL;
	oldpwd->prev = NULL;
	oldpwd->next = NULL;
	ft_entry_addb(&envs->exp, oldpwd);
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
		empty_envs(envs);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "OLDPWD", 6) == 0)
		{
			i++;
			continue ;
		}
		ft_entry_addb(&envs->env, newentry(envp[i]));
		ft_entry_addb(&envs->exp, newentry(envp[i]));
		i++;
	}
	oldpwd(envp, envs);
	sort_alpha_ll(&envs->exp, ll_size(envs->exp));
	envs->env_ct = ll_size(envs->env);
	envs->exp_ct = ll_size(envs->exp);
	return (envs);
}
