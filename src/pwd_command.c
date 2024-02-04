/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 10:49:57 by randre            #+#    #+#             */
/*   Updated: 2024/02/04 20:44:04 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	pwd_command(void)
{
	char	*str;

	str = malloc(2048 * sizeof(char));
	if (!str)
		return ;
	getcwd(str, 2048);
	printf("%s\n", str);
	free(str);
}
