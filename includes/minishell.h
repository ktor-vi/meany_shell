/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:11 by randre            #+#    #+#             */
/*   Updated: 2024/05/06 15:21:01 by randre           ###   ########.fr       */
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


typedef enum s_tokens
{
	PIPE = 1,
	RIGHT,
	RIGHT_RIGHT,
	LEFT,
	LEFT_LEFT,
}	t_tokens;

typedef struct s_lexer
{
	char			*str;
	t_tokens		token;
	int				i;
	struct s_lexer	*next;
	struct s_lexer	*prev;
}	t_lexer;

typedef struct s_parser_tools
{
	t_lexer			*lexer_list;
	t_lexer			*redirections;
	int				num_redirections;
	struct s_tools	*tools;
}	t_parser_tools;

typedef struct s_tools
{

}	t_tools;

typedef struct s_simple_cmds
{
	char					**str;
	int						(*builtin)(t_tools *, struct s_simple_cmds *);
	int						num_redirections;
	char					*hd_file_name;
	t_lexer					*redirections;
	struct s_simple_cmds	*next;
	struct s_simple_cmds	*prev;
}	t_simple_cmds;

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
	t_tokens			token_type;
}						t_args;

typedef struct	s_line
{
	char		**lines;
	t_tokens		*token_type;		
}				t_line;

typedef struct s_command
{
	char				*path;
	t_args				**arg;
	char				**args;
	int					args_ct;
	pid_t				pid;
	int					fd;
	int					to_pipe;
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
	char					*args;
	char					**paths;
	char					**envp;
	struct s_simple_cmds	*simple_cmds;
	char					*pwd;
	char					*old_pwd;
	int						pipes;
	int						*pid;
	bool					heredoc;
	bool					reset;
	int						st_in;
	t_command				*cmd;
	t_lexer					*lexer_list;
	t_parse					*parsed;
}							t_minishell;


// LEXER
int						handle_quotes(int i, char *str, char del);
char					**lexer(char *line);
int						count_quotes(char *line);
t_tokens				check_token(int c);
int						add_node(char *str, t_tokens token, t_lexer **lexer_list);
t_lexer					*ft_lexernew(char *str, int token);
void					ft_lexeradd_back(t_lexer **lst, t_lexer *new);
int						token_reader(t_minishell *minishell);
int						handle_token(char *str, int i, t_lexer **lexer_list);


void					print_all_cmd(t_minishell *minishell);
t_command				*lastcmd(t_command *lst);
void					init_cmds(char *split_line);
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
int						count_quotes(char *line);
void					verify_quotes(char *line, int i, int *val);
void					handle_sigint(int sig);
int						is_builtin(t_command *cmd);
int						is_builtin_char(char **split_line);
int						ft_equalstr(char *s1, char *s2);
int						getchindex(char *s, int c);
void					free_tab(char **tab);
void					kb_quit(void);
void					reset_line(char *line);
void					reset_minishell(t_minishell *minishell);
int						mini_init(t_minishell *minishell);
t_simple_cmds			*ft_simple_cmdsnew(char **str,
	int num_redirections, t_lexer *redirections);
void					ft_simple_cmdsadd_back(t_simple_cmds **lst, t_simple_cmds *new);
void					ft_simple_cmds_rm_first(t_simple_cmds **lst);
void					ft_simple_cmdsclear(t_simple_cmds **lst);
t_simple_cmds			*ft_simple_cmdsfirst(t_simple_cmds *map);
void					free_arr(char **split_arr);
// ENV & EXPORT
t_envs					*build_envs(char **envp);
void					printenv(t_entry *n, t_command *cmd);
void					printexport(t_entry *exp, t_command *cmd);
void					printenv(t_entry *env, t_command *cmd);
void					export_cmd(t_envs *envs, char *var);
void					unset_cmd(t_envs *envs, char *var);
t_entry					*find_entryprev(t_entry *lst, char *to_find);
// ENV UTILS
char					*ft_expand(char c, int *i, char *line);
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
void					parent_process(int prev_pipe, int pfds[2]);

//ERRORS
int						ft_error(int error);
#endif
