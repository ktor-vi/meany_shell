/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:43:02 by randre            #+#    #+#             */
/*   Updated: 2024/04/23 14:04:37 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <ctype.h>

static int	ft_bfrspace(char *line, int i)
{
	int	y;

	y = 0;
	if (!line)
		return (0);
	while (line[i] && !isspace(line[i]))
	{
		y++;
		i++;	
	}
	return (y);
}

char	*ft_copy(char *line, int i)
{
	char	*true_line;
	int		length;
	int		y;

	length = ft_bfrspace(line, i);
	if (!length)
		return (NULL);
	true_line = malloc((length + 1) * sizeof(char));
	if (!true_line)
		return (NULL);
	y = 0;
	while (length--)
	{
		true_line[y] = line[i];
		i++;
		y++;
	}
	true_line[y] = 0;
	return (true_line);
}

int	ft_expand(char c, int i, char *line)
{
	int		diff;
	int		length;
	char	*true_line;
	char	*res;

	diff = 0;
	if (c == '$')
	{
		i++;
		true_line = ft_copy(line, i);
		if (!true_line)
			return (0);
		res = getenv(true_line);
		if (res)
			ft_printf(STDOUT_FILENO, "%s", res);
		/*else
			search for var in envp*/
		free(true_line);
	}
	else
		return (0);
}