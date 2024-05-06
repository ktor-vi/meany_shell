/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_lexer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 13:45:17 by randre            #+#    #+#             */
/*   Updated: 2024/05/06 14:14:07 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_quotes(int i, char *str, char del)
{
	int	j;

	j = 0;
	if (str[i + j] == del)
	{
		j++;
		while (str[i + j] != del && str[i + j])
			j++;
		j++;
	}
	return (j);
}

t_tokens	check_token(int c)
{
	static int	token_arr[3][2] = {
	{'|', PIPE},
	{'>', RIGHT},
	{'<', LEFT},
	};
	int			i;

	i = 0;
	while (i < 3)
	{
		if (token_arr[i][0] == c)
			return ((t_tokens)token_arr[i][1]);
		i++;
	}
	return ((t_tokens)0);
}

int	handle_token(char *str, int i, t_lexer **lexer_list)
{
	t_tokens	token;

	token = check_token(str[i]);
	if (token == RIGHT && check_token(str[i + 1]) == RIGHT)
	{
		if (!add_node(NULL, RIGHT_RIGHT, lexer_list))
			return (-1);
		return (2);
	}
	else if (token == LEFT && check_token(str[i + 1]) == LEFT)
	{
		if (!add_node(NULL, LEFT_LEFT, lexer_list))
			return (-1);
		return (2);
	}
	else if (token)
	{
		if (!add_node(NULL, token, lexer_list))
			return (-1);
		return (1);
	}	
	return (0);
}