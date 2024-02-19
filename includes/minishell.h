/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:11 by randre            #+#    #+#             */
/*   Updated: 2024/02/19 11:20:27 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"
# include <errno.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_entry
{
	char				*name;
	char				*value;
	struct s_entry		*next;
	struct s_entry		*prev;
}						t_entry;

typedef struct s_envs
{
	struct s_entry		*env;
	struct s_entry		*exp;
	size_t				env_ct;
	size_t				exp_ct;

}						t_envs;

typedef struct s_command
{
	char				*path;
	char				**args;
	int					args_ct;
	pid_t				pid;
	int					fd;
	bool				to_pipe;
	bool				end;
	int					pfds[2];
	int					exit_code;
	struct s_command	*next;
	struct s_command	*prev;
}						t_command;

typedef struct s_parse
{
	char				**tokens;
	int					tokens_ct;
}						t_parse;

typedef struct s_minishell
{
	int					st_in;
	int					st_out;
	char				*arg;
	t_command			*cmd;
	int					n_pipes;
	t_parse				*parsed;
	int					envp;
}						t_minishell;

void					print_all_cmd(t_minishell *minishell);
t_command				*lastcmd(t_command *lst);
void					ft_cmd_addb(t_minishell **mini, t_command *new);
void					print_all_cmd(t_minishell *minishell);
t_minishell				*populate(char **split_line, t_envs *envs);
t_command				*new_command(char **split_line, t_envs *envs, int s,
							int e, int fd);
void					check_command(char **split_line, t_envs *envs);
void					env_command(char **envp);
void					cd_command(char **);
void					pwd_command(t_command *cmd);
void					echo_command(char **split_line, t_command *cmd);
// UTILS
int	is_builtin(t_command *cmd);
int	is_builtin_char(char **split_line);
int						ft_equalstr(char *s1, char *s2);
int						getchindex(char *s, int c);
void					free_tab(char **tab);
void					kb_quit(void);
void					reset_line(char *line);
// ENV & EXPORT
t_envs					*build_envs(char **envp);
void					printenv(t_entry *n, t_command *cmd);
void					printexport(t_entry *exp, t_command *cmd);
void					printenv(t_entry *env, t_command *cmd);
void					export_cmd(t_envs *envs, char *var);
void					unset_cmd(t_envs *envs, char *var);
t_entry					*find_entryprev(t_entry *lst, char *to_find);
// ENV UTILS
t_entry					*swap(t_entry *ptr1, t_entry *ptr2);
void					sort_alpha_ll(t_entry **head, int count);
t_entry					*lastentry(t_entry *lst);
void					ft_entry_addb(t_entry **lst, t_entry *new);
t_entry					*newentry(char *var);
void					free_entry(t_entry *entry);
void					free_entry_alone(t_entry *entry_prev);
void					free_envs(t_envs **envs);
char					**ll_to_tab(t_entry *env);
int						ll_size(t_entry *env);
// EXEC
int						handle_builtins(t_command *cmd, t_envs *envs);
void					execute_pipes(t_minishell *minishell, t_envs *envs);
// EXEC UTILS
char					*get_cmdpath(char *cmd, t_entry *envp);
// EXEC HELPERS
void					dup2in_error(void);
void					dup2out_error(void);
void					forkfail_error(void);
void					create_pipe(int pfds[2]);
void					parent_process(int prev_pipe, int pfds[2],
							t_command **h);
#endif
