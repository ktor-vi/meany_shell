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
#define MINISHELL_H

#include "../libft/libft.h"
#include <stdio.h>

#include <readline/history.h>
#include <readline/readline.h>
#include <signal.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

typedef struct s_entry
{
	char			*name;
	char			*value;
	struct s_entry	*next;
	struct s_entry	*prev;
}					t_entry;

typedef struct s_envs
{
	struct s_entry	*env;
	struct s_entry	*exp;
	size_t			env_ct;
	size_t			exp_ct;

}					t_envs;

void check_command(char **split_line, char **envp);
void env_command(char **envp);
void cd_command(char **split_line);
void pwd_command(void);
void echo_command(char **split_line);
int ft_equalstr(char *s1, char *s2);
//UTILS
int	getchindex(char *s, int c);
//ENV & EXPORT
t_envs	*build_envs(char **envp);
void	printenv(t_entry *n);
void free_envs(t_envs **envs);
//ENV UTILS
t_entry	*swap(t_entry *ptr1, t_entry *ptr2);
void	sort_alpha_ll(t_entry **head, int count);
t_entry  *lastentry(t_entry *lst);
void	ft_entry_addb(t_entry **lst, t_entry *new);
t_entry	*newentry(char *var);

#endif
