
#include "../includes/minishell.h"
#include <fcntl.h>

int	redirect_handle(char **split_line, int j)
{
	int		fd;
	char	*true_name;

	true_name = ft_strqtrim(ft_strdup(split_line[j + 1]));
	fd = open(true_name, O_WRONLY);
	if (fd < 0)
	{
		fd = open(true_name, O_CREAT, 0666);
		close(fd);
		fd = open(true_name, O_WRONLY);
	}
	free(true_name);
	return (fd);
}

void	assign_here_doc(t_command *h, char **split_line, int i)
{
	int	k;

	k = -1;
	h->eof = NULL;
	h->heredoc = 0;
	while (split_line[++k])
	{
		if (ft_equalstr(split_line[i + k], "<<") && ft_equalstr(split_line[i],
				"<<"))
		{
			h->heredoc = 1;
			h->eof = ft_strdup(split_line[i + 1]);
			break ;
		}
		else if (ft_equalstr(split_line[i + k], "<<")
			&& !ft_equalstr(split_line[i], "<<"))
		{
			h->heredoc = -1;
			break ;
		}
	}
}

int	closed_quotes(char *line)
{
	int	i;
	int	type;

	i = 0;
	if (!line)
		return (0);
	while (line[i] != '"' && line[i] != 39 && line[i])
		i++;
	if (!line[i])
		return (0);
	else if (line[i] == '"')
		type = 2;
	else if (line[i] == 39)
		type = 1;
	i++;
	if (!line[i])
		return (0);
	while (line[i])
	{
		if (line[i] == '"' && type == 2)
			return (1);
		else if (line[i] == 39 && type == 1)
			return (2);
		else
			i++;
	}
	return (0);
}

char	*ft_strqtrim(char *line)
{
	char	*trimmed;
	char	*start;
	int		type;

	trimmed = malloc((ft_strlen(line) + 1) * sizeof(char));
	type = 0;
	start = trimmed;
	while (*line)
	{
		if (*line != 39 && *line != '"')
		{
			*trimmed = *line;
			line++;
			trimmed++;
		}
		else if (*line == 39)
		{
			if (type == 0)
			{
				type = 1;
				line++;
			}
			else if (type == 1)
			{
				type = 0;
				line++;
			}
			else
			{
				*trimmed = *line;
				line++;
				trimmed++;
			}
		}
		else if (*line == '"')
		{
			if (type == 0)
			{
				type = 2;
				line++;
			}
			else if (type == 2)
			{
				type = 0;
				line++;
			}
			else
			{
				*trimmed = *line;
				line++;
				trimmed++;
			}
		}
	}
	*trimmed = 0;
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

void	print_all_cmd(t_minishell *minishell)
{
	t_command	*h;
	int			j;
	int			i;

	j = 0;
	i = 0;
	h = minishell->cmd;
	while (h)
	{
		printf("Command %d : \n Path : %s, to pipe : %d - end %d\n", i, h->path,
			h->to_pipe, h->end);
		while ((h->args)[j])
		{
			printf("%d -- %s\n", j, (h->args)[j]);
			j++;
		}
		j = 0;
		h = h->next;
	}
}
