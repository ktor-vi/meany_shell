/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/01/18 15:16:20 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
int sig;

void handle_SIGINT(int sig) {
  sig = 0;
  printf("\n");
  rl_on_new_line();
  rl_replace_line("", 0);
  rl_redisplay();
}

void handle_SIGQUIT(int sig) {
  sig = 0;
  return;
}

int main(int argc, char **argv, char **envp) {
  char **split_line;
  char *line;
  int exit_flag;
  int i;
	t_envs *envs;

	(void)argc;
	(void)argv;
	envs = build_envs(envp);
  line = NULL;
  exit_flag = 0;
  signal(SIGINT, handle_SIGINT);
  signal(SIGQUIT, handle_SIGQUIT);
  while (true) {
    i = -1;
    line = readline("$ ");
    if (line && !ft_equalstr(line, "")) {
      split_line = ft_split(line, ' ');
      if (ft_equalstr(split_line[0], "exit"))
        exit_flag = 1;
      add_history(line);
      check_command(split_line, envs);
      while (split_line[++i])
        free(split_line[i]);
      free(split_line);
    }
    if (line)
      free(line);
    else
      exit_flag = 1;
    if (exit_flag == 1) {
      rl_clear_history();
      exit(0);
    }
  }
  return (0);
}
