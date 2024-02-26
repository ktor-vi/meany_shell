/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 13:18:26 by randre            #+#    #+#             */
/*   Updated: 2024/02/26 13:41:06 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <string.h>
#include <ctype.h>

void	verify_quotes(char *line, int i, int *val)
{
	if ((*val == 1 && line[i] == '"') || (*val == 2 && line[i] == 39))
	{
		*val = 0;
		return ; 
	}
	i++;
	while(line[i])
	{
		if (line[i] == '"')
		{
			*val = 1;
			return ;
		}
		else if (line[i] == 39)
		{
			*val = 2;
			return ;
		}
		else
			i++;
	}
	*val = 0;
	return ;
}

char	*ft_strndup(const char *s, int n)
{
	char	*str;
	char	*start;

	if (!s)
		return (NULL);
	str = malloc((n + 1) * sizeof(char));
	if (!str)
		return (NULL);
	start = str;
	while (n--)
	{
		*str = *s;
		s++;
		str++;
	}
	*str = '\0';
	return (start);
}

void	new_token(t_token *token)
{
	t_token	*new;
	
	new = malloc(sizeof(t_token) * 1);
	token->next = new;
	new->next = NULL;
	new->prev = token;
	new->line = NULL;
	//new->type = NULL;
}

void	get_token_type(t_token *token)
{
	int	i;

	i = -1;
	while (token->line[++i])
	{
		if (token->line[i] == '>')
		{
			if (token->line[i + 1] == '>')
				token->type = TOKEN_DRCHEVRON;
			else
				token->type = TOKEN_RCHEVRON;
			return ;
		}
		if (token->line[i] == '<')
		{
			if (token->line[i + 1] == '<')
				token->type = TOKEN_DLCHEVRON;
			else
				token->type = TOKEN_LCHEVRON;
			return ;
		}
		if (token->line[i] == '|')
		{
			token->type = TOKEN_PIPE;
			return ;
		}
		if (token->line[i] == '$')
		{
			token->type = TOKEN_VAR;
			return ;
		}
	}
	token->type = TOKEN_WORD;
}

int	isspecial(char c)
{
	if  (c == '>' || c == '<' || c == '|')
		return (1);
	else
		return (0);
}

t_token	*lexer(char *line)
{
	int		i;
	int		j;
	int		in_quotes;
	t_token	*token;
	t_token	*start;

	i = 0;
	j = 0;
	token = malloc(sizeof(t_token) * 1);
	start = token;
	token->prev = NULL;
	in_quotes = 0;
	if (!line)
		return (NULL);
	while (line[i] != 0)
	{
		if (line[i] == '"' || line[i] == 39)
			verify_quotes(line, i, &in_quotes);
		//printf("char : %c, quotes : %d\n", line[i], in_quotes);
		/*if (isspecial(line[i]) && in_quotes == 0)
		{
			
		}*/
		if (isspace(line[i]) && in_quotes == 0)
		{
			token->line = ft_strndup(&line[i - j], j);
			token->space = 1;
			get_token_type(token);
			new_token(token);
			token = token->next;
			i++;
			if (isspace(line[i]))
				while (isspace(line[i]))
					i++;
			if (!line[i])
				break ;
			j = 0;
		}
		else
		{
			i++;
			j++;
		}
	}
	token->line = ft_strndup(&line[i - j], j);
	get_token_type(token);
	new_token(token);
	return (start);
}

int main(void)
{
	char *line;
	t_minishell	*minishell;

	line = readline("$ ");
	minishell = parser(lexer(line), NULL);
	t_command	*h;
	int			j;
	int			i;

	j = 1;
	i = 0;
	h = minishell->cmd;
	while (h)
	{
		printf("Command %d : %s\nto pipe : %d - end %d\n", i,  h->args[0],
			h->to_pipe, h->end);
		j = 0;
		h = h->next;
	}
}