#include "../includes/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

typedef struct s_data
{
	int		fd_in;
	int		fd_out;
	pid_t	pid;
}			t_data;

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i++])
		free(tab[i]);
	free(tab);
	tab = NULL;
}


char	*get_cmdpath(char *cmd, t_entry *envp)
{
	int		i;
	char	*path;
	char	**paths;
	char	*temp_env;

	i = 0;
	if(access(cmd, X_OK) == 0)
		return (cmd);
	while (envp && ft_strnstr(envp->name, "PATH", 4) == 0 )
		envp = envp->next;
	if (!envp)
		return (NULL);
	path = ft_strdup(envp->value);
	paths = ft_split(path, ':');
	while (paths[i])
	{
		temp_env = ft_strjoin(paths[i], "/");
		temp_env = ft_strjoin(temp_env, cmd);
		if (access(temp_env, X_OK) == 0)
			return (temp_env);
		free(temp_env);
		i++;
	}
	free_tab(paths);
	free(path);
	return (NULL);
}

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
	int		pfd[2];

	if (pipe(pfd) == -1)
	{
		perror("pipe() error");
		exit(EXIT_FAILURE);
	}
	data->pid = fork();
	if (data->pid == 0)
		ft_here_doc_child(pfd, eof);
	else
	{
		close(pfd[1]);
		if (dup2(pfd[0], STDIN_FILENO) == -1)
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
