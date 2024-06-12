/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 20:46:58 by vphilipp          #+#    #+#             */
/*   Updated: 2024/06/12 17:37:07 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*ft_loop(char *t_path, char **paths, char *cmd, char *path)
{
	int		i;
	char	*temp_env;

	i = 0;
	while (paths[i])
	{
		t_path = ft_strjoin(paths[i], "/");
		temp_env = ft_strjoin(t_path, cmd);
		if (access(temp_env, X_OK) == 0)
		{
			free_tab(paths);
			free(path);
			return (temp_env);
		}
		free(temp_env);
		i++;
	}
	return (NULL);
}

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
	temp_env = ft_loop(t_path, paths, cmd, path);
	if (temp_env == NULL)
	{
		free_tab(paths);
		free(path);
	}
	return (temp_env);
}

void	set_paths(t_command *cmds, t_envs *envs)
{
	t_command	*lst;

	lst = cmds;
	while (lst)
	{
		if (!is_builtin(lst) && !ft_strchr(lst->args[0], '/')
			&& get_cmdpath(lst->args[0], envs->exp) != NULL)
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

void	no_path(t_command *h)
{
	g_exit_codes = 127;
	ft_printf(STDERR_FILENO, "minishell: %s: command not found\n", h->args[0]);
}

void	last_cmd_child(int prev_pipe, t_command *h, t_envs *envs, int *st)
{
	if (prev_pipe != STDIN_FILENO && dup2(prev_pipe, STDIN_FILENO) == -1)
		dup2in_error();
	if (dup2(h->fd, STDOUT_FILENO) == -1)
		dup2out_error();
	if (h->heredoc == true)
		here_doc(h, envs, st);
	else
		handle_execve(h, envs);
	close(prev_pipe);
	exit(EXIT_FAILURE);
}
