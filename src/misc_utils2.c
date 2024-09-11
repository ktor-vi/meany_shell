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

int sl_is_tokens(char **split_line)
{
    int i;
    int res;

    i = 0;
    res = 1;
    while(split_line[i])
    {
        if(!is_tok(split_line, i))
            res = 0;
        i++;
    }
    return (res);
}

int sl_is_heredoc(char **split_line)
{
    if(ft_equalstr(split_line[0], "<") && ft_equalstr(split_line[1], "<") && !split_line[3])
        {
            here_doc_alone(split_line[2]);
            return (1);
        }
    else
        return (0);
}
