/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 15:05:45 by randre            #+#    #+#             */
/*   Updated: 2024/02/26 13:46:59 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>

t_command	*new_command(char **split_line, int y, int to_pipe, int fd)
{
	t_command	*new;
	int			i;

	new = malloc(sizeof(t_command) * 1);
	new->fd = fd;
	new->next = NULL;
	i = y;
	while (split_line[i])
		i++;
	new->args = malloc((i + 1) * sizeof(char*));
	i = 0;
	while (split_line[y])
	{
		new->args[i] = malloc((ft_strlen(split_line[y] + 1) * sizeof(char)));
		new->args[i] = ft_strdup(split_line[y]);
		y++;
		i++;
	}
	if (to_pipe)
		new->to_pipe = 1;
	return (new);
}

char	*ft_noqstrdup(const char *s, t_token *token)
{
	char	*str;
	char	*start;
	int		quotes;

	if (!s)
		return (NULL);
	str = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	start = str;
	quotes = 0;
	while (*s)
	{
		if (*s != '"' && *s != 39 && token->in_quotes)
		{
			if (*s == '|' && !quotes)
				break;
			*str = *s;
			s++;
			str++;
		}
		else if (token->in_quotes)
		{
			if (quotes == 0)
				quotes = 1;
			else
				quotes = 0;
		}
	}
	*str = '\0';
	return (start);
}

t_command	*lastcmd(t_command *lst)
{
	t_command	*ptr;

	ptr = lst;
	if (ptr == NULL)
		return (NULL);
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

int	redirect_handle(char *line)
{
	int	fd;

	fd = open(line, O_WRONLY);
	if (fd < 0)
	{
		fd = open(line, O_CREAT, 0666);
		close(fd);
		fd = open(line, O_WRONLY);
	}
	free(line);
	return (fd);
}

void	ft_cmd_addb(t_minishell **mini, t_command *new)
{
	t_command	*last;

	if (new == NULL)
		return ;
	new->next = NULL;
	new->prev = NULL;
	last = lastcmd((*mini)->cmd);
	new->prev = last;
	if (last != NULL)
		last->next = new;
	else
		(*mini)->cmd = new;
}

t_minishell	*parser(t_token *token, t_envs *envs)
{
	t_minishell	*minishell;
	char		**split_line;
	int			i;
	int			start_y;
	int			y;
	int			fd;
	int			in_quotes;

	split_line = ft_calloc(2048, 1);
	minishell = malloc(sizeof(t_minishell) * 1);
	minishell->cmd = NULL;
	y = 0;
	start_y = 0;
	in_quotes = 0;
	fd = STDOUT_FILENO;
	while (token)
	{
		i = 0;
		split_line[y] = ft_calloc(2048, sizeof(char));
		if (!token->line)
			break;
		ft_printf(1, "Line : %s\n Type : %u\n\n", token->line, token->type);
		while (token->line[i])
		{
			// if (token->type == TOKEN_RCHEVRON)
			// {
			// 	while (token->line[i] != '>')
			// 		i++;
			// 	if (i > 0)
			// 	{
			// 		split_line[y] = ft_strndup(token->line, i);
			// 		y++;
			// 	}
			// 	if (token->line[i + 1])
			// 		fd = redirect_handle(ft_noqstrdup(&token->line[i], token));
			// 	else
			// 	{
			// 		token = token->next;
			// 		if (!token)
			// 			return (NULL);
			// 		fd = redirect_handle(ft_noqstrdup(token->line, token));
			// 	}
			// }
			// else if (token->line[i] == '|')
			// {
			// 	if (i > 0)
			// 		split_line[y] = ft_strndup(token->line, i - 1);
			// 	ft_cmd_addb(&minishell, new_command(split_line, start_y, 1, fd));
			// 	if (i > 0)
			// 		y++;
			// 	if (token->line[i + 1])
			// 	{
			// 		start_y = y;
			// 		split_line[y] = ft_strdup(&token->line[i + 1]);
			// 		y++;
			// 	}
			// }
			if (token->type == TOKEN_WORD)
			{
				split_line[y] = ft_noqstrdup(token->line, token);
				//ft_printf(1, "line : %s", split_line[y]);
				y++;
				break;
			}
		}
		token = token->next;
	}
	ft_cmd_addb(&minishell, new_command(split_line, start_y, 0, fd));
	while (y--)
	{
		write(1, "1\n", 2);
		free(split_line[y]);
	}
	free(split_line);
	return (minishell);
}
