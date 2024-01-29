/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:28:12 by randre            #+#    #+#             */
/*   Updated: 2024/01/08 14:57:28 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int ft_equalstr(char *s1, char *s2) {
  int i;

  i = 0;
  while (s1[i] == s2[i]) {
    if (s1[i] == '\0')
      return (1);
    i++;
  }
  return (0);
}

int	getchindex(char *s, int c)
{
	int i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
