#include "../includes/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct s_data
{
	int		fd_in;
	int		fd_out;
	int		pfd[2];
	pid_t	pid;
}			t_data;

static void	ft_here_doc_child(int *pfd, char *eof)
{
	char	*line;

	line = NULL;
	close(pfd[0]);
	while (ft_strncmp(line, eof, ft_strlen(eof)) != 0)
	{
		write(pfd[1], line, ft_strlen(line));
		free(line);
		write(1, "> ", 2);
		line = get_next_line(0);
	}
}

void	ft_here_doc(t_data *data, t_command *cmd, char *eof)
{
	if (pipe(data->pfd) == -1)
	{
		perror("pipe() error");
		exit(EXIT_FAILURE);
	}
	data->pid = fork();
	if (data->pid == -1)
	{
		perror("fork() error");
		exit(EXIT_FAILURE);
	}
	if (data->pid == 0)
		ft_here_doc_child(data->pfd, eof);
	else
	{
		close(data->pfd[1]);
		if (dup2(data->pfd[0], STDIN_FILENO) == -1)
		{
			perror("dup2() error");
			exit(EXIT_FAILURE);
		}
		waitpid(data->pid, NULL, 0);
		if (execve(cmd->path, cmd->args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	}
}
int	main(int argc, char **argv)
{
	t_entry		*envp;
	t_command	*cmd;
	t_data		*data;

	if (argc != 3)
		exit(1);
	data = (t_data *)malloc(sizeof(t_data));
	cmd = (t_command *)malloc(sizeof(t_command));
	cmd->args = malloc(sizeof(char *) * 2);
	envp = malloc(sizeof(t_entry));
	envp->name = "PATH";
	envp->value = getenv("PATH");
	envp->next = NULL;
	cmd->path = get_cmdpath(argv[1], envp);
	ft_here_doc(data, cmd, argv[2]);
}
