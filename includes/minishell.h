/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:11 by randre            #+#    #+#             */
/*   Updated: 2024/01/18 11:05:01 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_entry
{
	char			*name;
	char			*value;
	struct s_entry	*next;
}					t_entry;

typedef struct s_envs
{
	struct s_entry	*env;
	struct s_entry	*exp;
	size_t			env_ct;
	size_t			exp_ct;

}					t_envs;

typedef struct s_command
{
	char			*path;
	char			**args;
	int				args_ct;
	pid_t			pid;
	int				fd_in;
	int				fd_out;
	int				exit_code;
}					t_command;

typedef struct s_parse
{
	char			**tokens;
	int				tokens_ct;
}					t_parse;

typedef struct s_minishell
{
	int				st_in;
	int				st_out;
	char			*arg;
	t_command		*cmd;
	int				cmds;
	t_parse			*parsed;
	int				envp;
}					t_minishell;

void				check_command(char **split_line, t_envs *envs);
void				env_command(char **envp);
void				cd_command(char **split_line);
void				pwd_command(void);
void				echo_command(char **split_line);
// UTILS
int					ft_equalstr(char *s1, char *s2);
int					getchindex(char *s, int c);
// ENV & EXPORT
t_envs				*build_envs(char **envp);
void				printenv(t_entry *n);
void				printexport(t_entry *exp);
void				printenv(t_entry *env);
void				export_cmd(t_envs *envs, char *var);
void				unset_cmd(t_envs *envs, char *var);
t_entry				*find_entryprev(t_entry *lst, char *to_find);
// ENV UTILS
t_entry				*swap(t_entry *ptr1, t_entry *ptr2);
void				sort_alpha_ll(t_entry **head, int count);
t_entry				*lastentry(t_entry *lst);
void				ft_entry_addb(t_entry **lst, t_entry *new);
t_entry				*newentry(char *var);
void				free_entry(t_entry *entry);
void				free_envs(t_envs **envs);

#endif
