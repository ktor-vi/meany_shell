/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:11 by randre            #+#    #+#             */
/*   Updated: 2024/01/18 10:52:22 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"

void	check_command(char **split_line, char **envp);
void	env_command(char **envp);
void	cd_command(char **split_line);
void	pwd_command(void);
void	echo_command(char **split_line);
int		ft_strcmp(char *s1, char *s2);

#endif