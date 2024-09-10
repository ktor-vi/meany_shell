/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:32:24 by randre            #+#    #+#             */
/*   Updated: 2024/09/10 14:32:46 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	preserve_st(int *st)
{
	st[0] = dup(STDIN_FILENO);
	st[1] = dup(STDOUT_FILENO);
}

void	close_st(int *st)
{
	close(st[0]);
	close(st[1]);
}

char	*new_shlvl(char *base)
{
	char	*incremented;
	int		base_n;

	base_n = ft_atoi(base);
	if (base_n >= 1000)
		base_n = 0;
	if (base_n < 0)
		base_n = -1;
	incremented = ft_itoa(base_n + 1);
	free(base);
	return (incremented);
}
