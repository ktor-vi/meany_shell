#include "../includes/minishell.h"

void	ft_here_doc_last(t_command *h, t_envs *envs)
{
	char	*line;
	int		pid;
	int		pfds[2];

	line = NULL;
	if (pipe(pfds) == -1)
	{
		perror("pipe() error");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		while (ft_strcmp(line, h->eof) != 0)
		{
			write(pfds[1], line, ft_strlen(line));
			free(line);
			write(1, "> ", 2);
			line = get_next_line(STDIN_FILENO);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pfds[1]);
		if (dup2(pfds[0], STDIN_FILENO) == -1)
		{
			perror("dup2() error");
			exit(EXIT_FAILURE);
		}
		waitpid(pid, NULL, 0);
		execve(h->path, h->args, ll_to_tab(envs->env));
	}
}

 void	ft_here_doc_piped(t_command *h, t_envs *envs, int *pfds)
{
	char	*line;
	int		pid;

	line = NULL;
	if (pipe(pfds) == -1)
	{
		perror("pipe() error");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		while (ft_strncmp(line, h->eof, ft_strlen(h->eof)) != 0)
		{
			write(pfds[1], line, ft_strlen(line));
			free(line);
			write(STDIN_FILENO, "> ", 2);
			line = get_next_line(STDIN_FILENO);
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		close(pfds[1]);
		if (dup2(pfds[0], STDIN_FILENO) == -1)
		{
			perror("dup2() error");
			exit(EXIT_FAILURE);
		}
		waitpid(pid, NULL, 0);
		execve(h->path, h->args, ll_to_tab(envs->env));
	}
}
