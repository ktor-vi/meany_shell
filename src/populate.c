
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
	int			args_ct;
	t_minishell	*minishell;

	i = 0;
	j = 0;
	fd = STDOUT_FILENO;
	args_ct = 0;
	while (split_line[args_ct] != NULL)
		args_ct++;
	minishell = malloc(sizeof(t_minishell));
	minishell->cmd = NULL;
	minishell->n_pipes = 0;
	while (split_line[j] != NULL)
	{
		if (ft_equalstr(split_line[j], "|"))
		{
			ft_cmd_addb(&minishell, new_command(split_line, envs, i, j, fd));
			minishell->n_pipes++;
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

t_command	*new_command(char **split_line, t_envs *envs, int s, int e, int fd)
{
	t_command	*new;
	int			i;

	i = 0;
	new = malloc(sizeof(t_command));
	new->args_ct = e - s;
	new->fd = fd;
	new->path = get_cmdpath(split_line[s], envs->env);
	if (s == e)
	{
		new->args[i] = ft_strdup(split_line[s + i]);
		new->args_ct = 1;
		return (new);
	}
	else
		new->args = malloc((e - s + 1) * sizeof(char *));
	while (i < new->args_ct)
	{
		if (ft_equalstr(split_line[s + i], ">"))
			break;
		new->args[i] = ft_strdup(split_line[s + i]);
		i++;
	}
	if (ft_equalstr(split_line[e], "|"))
		new->to_pipe = true;
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
