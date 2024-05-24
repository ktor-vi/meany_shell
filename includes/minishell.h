/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:11 by randre            #+#    #+#             */
/*   Updated: 2024/05/08 14:08:20 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../bigft/ft_printf/ft_printf.h"
# include "../bigft/get_next_line/get_next_line.h"
# include "../bigft/libft/libft.h"
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

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

typedef struct s_arg
{
	char				*line;
	int					in_quotes;
}						t_args;

typedef struct s_command
{
	char				*path;
	t_args				**arg;
	char				**args;
	int					args_ct;
	pid_t				pid;
	int					fd;
	int					heredoc;
	int					to_pipe;
	char				*eof;
	char				*next_tok;
	int					end;
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

// int						g_exit_codes[2];

// PARSING
char					**lexer(char *line, t_envs *envs);
void					print_all_cmd(t_minishell *minishell);
t_command				*lastcmd(t_command *lst);
void					init_cmds(char *split_line);
void					ft_cmd_addb(t_minishell **mini, t_command *new);
void					print_all_cmd(t_minishell *minishell);
t_minishell				*populate(char **split_line, t_envs *envs);
int						calc_offset(char **split_line, int pos);
t_command				*build_command(char **split_line, int pos, int fd);
t_command				*alloc_command(char **split_line, int pos, int fd);
int						redirect_handle(char **split_line, int j);

int						is_builtin_char_pos(char **split_line, int pos);
t_minishell				*populate_cmds(char **split_line, t_envs *envs);
void					post_parse(t_minishell *minishell, t_envs *envs);
void					set_paths(t_command *cmds, t_envs *envs);
t_command				*new_command(char **split_line, t_envs *envs, int s,
							int e, int fd);
void					check_command(char **split_line, t_envs *envs);
void					env_command(char **envp);
void					cd_command(char **);
void					pwd_command(t_command *cmd);
void					echo_command(char **split_line, t_command *cmd);
// UTILS
void					verify_quotes(char *line, int i, int *val);
void					handle_sigint(int sig);
int						is_builtin(t_command *cmd);
int						is_builtin_char(char **split_line);
int						ft_equalstr(char *s1, char *s2);
int						getchindex(char *s, int c);
void					free_tab(char **tab);
void					kb_quit(void);
char					*ft_strqtrim(char *line);
void					reset_line(char *line);
// ENV & EXPORT
void					printtab(char **exp);
char					*envs_search(t_envs *envs, char *to_find);
t_envs					*build_envs(char **envp);
void					printenv(t_entry *n, t_command *cmd);
void					printexport(t_entry *exp, t_command *cmd);
void					printenv(t_entry *env, t_command *cmd);
void					export_cmd(t_envs *envs, char **vars);
void					unset_cmd(t_envs *envs, char *var);
t_entry					*find_entryprev(t_entry *lst, char *to_find);
// ENV UTILS
char					*ft_expand(char c, int *i, char *line, t_envs *envs);
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
int	pre_pipe(t_command *cmd);
int	pre_heredoc(t_command *cmd);
int						handle_builtins(t_command *cmd, t_envs *envs);
void					execute_pipes(t_minishell *minishell, t_envs *envs);
void	ft_here_doc_last(t_command *h, t_envs *envs);
void	ft_here_doc_piped(t_command *h, t_envs *envs, int *pfds);
// EXEC UTILS
char					*get_cmdpath(char *cmd, t_entry *envp);
// EXEC HELPERS
void					dup2in_error(void);
void					dup2out_error(void);
void					forkfail_error(void);
void					create_pipe(int pfds[2]);
void					parent_process(int prev_pipe, int pfds[2]);
// ERRORS
int						ft_error(int code, char **split_line, char *line,
							int i);
#endif
