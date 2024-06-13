/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:28:12 by randre            #+#    #+#             */
/*   Updated: 2024/06/12 15:33:59 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_equalstr(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	while (s1[i] == s2[i])
	{
		if (s1[i] == '\0')
			return (1);
		i++;
	}
	return (0);
}

int	getchindex(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	kb_quit(t_envs *envs)
{
	rl_clear_history();
	free_envs(envs);
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 5);
	exit(0);
}

void	reset_line(char *line)

{
	free(line);
	line = NULL;
}
