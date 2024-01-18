/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:49:57 by randre            #+#    #+#             */
/*   Updated: 2024/01/18 10:51:56 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_command(void)
{
	char	*str;

	str = malloc(2048 * sizeof(char));
	getcwd(str, 2048);
	printf("%s\n", str);
	free(str);
}