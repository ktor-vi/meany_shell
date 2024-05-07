
#include "../includes/minishell.h"
#include <fcntl.h>

int	redirect_handle(char **split_line, int j)
{
	int	fd;

	fd = open(split_line[j + 1], O_WRONLY);
	if (fd < 0)
	{
		fd = open(split_line[j + 1], O_CREAT, 0666);
		close(fd);
		fd = open(split_line[j + 1], O_WRONLY);
	}
	return (fd);
}

t_minishell	*populate(char **split_line, t_envs *envs)
{
	int			i;
	int			j;
	int			fd;
	t_minishell	*minishell;

	i = 0;
	j = 0;
	fd = STDOUT_FILENO;
	minishell = malloc(sizeof(t_minishell));
	minishell->cmd = NULL;
	while (split_line[j] != NULL)
	{
		if (ft_strcmp(split_line[j], "|") == 0)
		{
			ft_cmd_addb(&minishell, new_command(split_line, envs, i, j, fd));
			i = j + 1;
			fd = STDOUT_FILENO;
		}
		else if (ft_equalstr(split_line[j], ">"))
		{
			fd = redirect_handle(split_line, j);
			j++;
		}
		j++;
	}
	ft_cmd_addb(&minishell, new_command(split_line, envs, i, j, fd));
	return (minishell);
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

t_command	*new_command(char **split_line, t_envs *envs, int s, int e, int fd)
{
	t_command	*new;
	int			i;

	i = 0;
	new = malloc(sizeof(t_command));
	new->args_ct = e - s;
	if (new->args_ct == 0)
		new->args_ct = 1;
	new->arg = malloc(new->args_ct * sizeof(t_args*));
	new->args = malloc((new->args_ct + 1) * sizeof(char *));
	new->fd = fd;
	new->path = get_cmdpath(ft_strtrim(split_line[s], " "), envs->env);
	while (i < new->args_ct)
	{
		if (ft_equalstr(split_line[s + i], ">") || ft_equalstr(split_line[s + i], ">>") || ft_equalstr(split_line[s + i], "<") || ft_equalstr(split_line[s + i], "<<"))
			break ;
		new->arg[i] = malloc(1 * sizeof(t_args));
		new->arg[i]->in_quotes = closed_quotes(split_line[s + i]);
		if (new->arg[i]->in_quotes)
		{
			new->arg[i]->line = ft_strqtrim(ft_strdup(split_line[s + i]));
			new->args[i] = ft_strqtrim(ft_strdup(split_line[s + i]));
		}
		else
		{
			new->arg[i]->line = ft_strdup(split_line[s + i]);
			new->args[i] = ft_strdup(split_line[s + i]);
		}
		i++;
	}
	if (ft_equalstr(split_line[e], "|"))
		new->to_pipe = true;
	else
		new->to_pipe = false;
	new->args[i] = NULL;
	return (new);
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
