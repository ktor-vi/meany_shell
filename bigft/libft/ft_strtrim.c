/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:35:42 by vphilipp          #+#    #+#             */
/*   Updated: 2024/05/06 15:17:11 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

int	begin_chars(char const *s1, char const *set)
{
	int	i;
	int	j;
	int	char_at_begin;

	j = 0;
	char_at_begin = 0;
	while (s1[j])
	{
		i = 0;
		while (set[i])
		{
			if (s1[j] == set[i])
			{
				char_at_begin++;
				break ;
			}
			i++;
		}
		if (set[i] == '\0')
			return (char_at_begin);
		j++;
	}
	return (char_at_begin);
}

int	end_chars(char const *s1, char const *set, int len)
{
	int	i;
	int	char_at_end;

	len -= 1;
	char_at_end = 0;
	while (len >= 0)
	{
		i = 0;
		while (set[i])
		{
			if (s1[len] == set[i])
			{
				char_at_end++;
				break ;
			}
			i++;
		}
		if (set[i] == '\0')
			return (char_at_end);
		len--;
	}
	return (char_at_end);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		char_at_begin;
	int		new_len;
	int		len_s1;
	char	*trimmed;
	int		i;

	if ((!s1 || !set) || (!s1 && !set))
		return (0);
	i = 0;
	char_at_begin = begin_chars(s1, set);
	len_s1 = ft_strlen(s1);
	new_len = len_s1 - (char_at_begin + end_chars(s1, set, len_s1));
	if (new_len <= 0)
		new_len = 1;
	trimmed = malloc((new_len * sizeof(char)) + 1);
	if (!trimmed)
		return (0);
	while (i < new_len)
	{
		trimmed[i] = s1[char_at_begin + i];
		i++;
	}
	trimmed[i] = '\0';
	return (trimmed);
}
