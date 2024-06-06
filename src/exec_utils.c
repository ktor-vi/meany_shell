/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:46:58 by vphilipp          #+#    #+#             */
/*   Updated: 2024/06/06 12:53:40 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_cmdpath(char *cmd, t_entry *envp)
{
	int		i;
	char	*path;
	char	*t_path;
	char	**paths;
	char	*temp_env;

	i = 0;
	if (access(cmd, X_OK) == 0)
		return (cmd);
	while (envp && ft_strnstr(envp->name, "PATH", 4) == 0)
		envp = envp->next;
	if (!envp)
		return (NULL);
	path = ft_strdup(envp->value);
	paths = ft_split(path, ':');
	while (paths[i])
	{
		t_path = ft_strjoin(paths[i], "/");
		temp_env = ft_strjoin(t_path, cmd);
		if (access(temp_env, X_OK) == 0)
			return (temp_env);
		free(temp_env);
		i++;
	}
	free_tab(paths);
	free(path);
	return (NULL);
}

void	set_paths(t_command *cmds, t_envs *envs)
{
	t_command	*lst;

	lst = cmds;
	while (lst)
	{
		if (!is_builtin(lst) && !ft_strchr(lst->args[0], '/') && get_cmdpath(lst->args[0], envs->exp) != NULL)
		{
			lst->path = ft_strdup(get_cmdpath(lst->args[0], envs->exp));
		}
		else
		{
			lst->path = NULL;
			g_exit_codes = 127;
		}
		lst = lst->next;
	}
}

// int	redirect_handle(char **split_line, int j)
// {
// 	int		fd;
// 	char	*true_name;
//
// 	true_name = ft_strqtrim(ft_strdup(split_line[j + 1]));
// 	fd = open(true_name, O_WRONLY);
// 	if (fd < 0)
// 	{
// 		fd = open(true_name, O_CREAT, 0666);
// 		close(fd);
// 		fd = open(true_name, O_WRONLY);
// 	}
// 	free(true_name);
// 	return (fd);
// }
