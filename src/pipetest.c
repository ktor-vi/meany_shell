
int	test(void)
{
	t_entry	*envp;
	t_minishell *minishell = malloc(sizeof(t_minishell));

	envp = malloc(sizeof(t_entry));
	envp->name = "PATH";
	envp->value = getenv("PATH");
	envp->next = NULL;
	minishell->n_pipes = 3;
	t_command ls = {.args = (char *[]){"ls", "-l", NULL}};
    t_command wc = {.args = (char *[]){"wc", "-l", NULL}};
    t_command xargs = {.args = (char *[]){"xargs", "printf", "0x%x\n", NULL}};
    t_command cowsay = {.args = (char *[]){"cowsay", NULL}};
	ls.path = get_cmdpath("ls", envp);
	wc.path = get_cmdpath("wc", envp);
	xargs.path = get_cmdpath("xargs", envp);
	cowsay.path = get_cmdpath("cowsay", envp);
	ls.next = &wc;
	wc.next = &xargs;
	xargs.next = &cowsay;
	cowsay.next = NULL;
	t_command *h = &ls;
	int i;
	i = 0;
	int prev_pipe, pfds[2];
	prev_pipe = STDIN_FILENO;
	while(i++ < minishell->n_pipes)
	{
		pipe(pfds);
		if (fork() == 0)
		{
			// Redirect previous pipe to stdin
			if (prev_pipe != STDIN_FILENO)
			{
				dup2(prev_pipe, STDIN_FILENO);
				close(prev_pipe);
			}
			// Redirect stdout to current pipe
			dup2(pfds[1], STDOUT_FILENO);
			close(pfds[1]);
			// Start command
			execve(h->path, h->args, NULL);
			perror("execvp failed");
			exit(1);
		}
		// Close read end of previous pipe (not needed in the parent)
		close(prev_pipe);
		// Close write end of current pipe (not needed in the parent)
		close(pfds[1]);
		// Save read end of current pipe to use in next iteration
		prev_pipe = pfds[0];
		h = h->next;
	}
	// Get stdin from last pipe
	if (prev_pipe != STDIN_FILENO)
	{
		dup2(prev_pipe, STDIN_FILENO);
		close(prev_pipe);
	}
	// Start last command
			execve(h->path, h->args, NULL);
	perror("execvp failed");
	exit(1);
}
