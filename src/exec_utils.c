/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:46:58 by vphilipp          #+#    #+#             */
/*   Updated: 2024/02/04 20:47:05 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmdpath(char **cmd, t_entry *envp)
{
	int		i;
	int		j;
	char	*path;
	char	**paths;
	char	*temp_env;

	i = 0;
	j = 0;
	while (ft_strnstr(envp->name, "PATH", 4) == 0)
		envp = envp->next;
	path = ft_strdup(envp->value);
	paths = ft_split(path, ':');
	while (paths[j])
	{
		temp_env = ft_strjoin(paths[j], "/");
		temp_env = ft_strjoin(temp_env, cmd[0]);
		if (access(temp_env, X_OK) == 0)
			return (temp_env);
		free(temp_env);
		j++;
	}
	free(paths);
	free(path);
	return (NULL);
}
