/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 13:36:17 by randre            #+#    #+#             */
/*   Updated: 2024/02/01 16:34:33 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


void handle_SIGINT(int sig) {
    if (sig == SIGINT) {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
}

void handle_SIGQUIT(int sig) {
    if (sig == SIGQUIT)
        return;
}

int main(int argc, char **argv, char **envp) {
    char **split_line;
    char *line;
    t_envs *envs;
    t_minishell *minishell;
		int i = 0;
    (void)argc;
    (void)argv;

    envs = build_envs(envp);
    line = NULL;

    signal(SIGINT, handle_SIGINT);
    signal(SIGQUIT, handle_SIGQUIT);

    while (true) {
        line = readline("$ ");
        
        if (!line) {
            write(1, "k\n", 2);
        } else if (!ft_equalstr(line, "")) {
            split_line = ft_split(line, ' ');
            add_history(line);

            minishell = populate(split_line, envs);
            minishell->st_in = dup(STDIN_FILENO);
            if (!handle_builtins(minishell->cmd, envs)) {
                execute_pipes(minishell, envs->env);
                dup2(minishell->st_in, STDIN_FILENO);
            }
            // Free allocated memory
            while (split_line[i++]) {
                free(split_line[i]);
            }
            free(split_line);
        }
        if (line) {
            free(line);
            line = NULL;
        } else {
            rl_clear_history();
            exit(0);
        }
    }

    return 0;
}
