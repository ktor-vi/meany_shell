/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:44:23 by vphilipp          #+#    #+#             */
/*   Updated: 2023/10/30 16:25:10 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*str;
	size_t	len1;
	size_t	len2;

	i = -1;
	j = -1;
	len1 = gnl_strlen(s1);
	len2 = gnl_strlen(s2);
	str = malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
	{
		free(s1);
		return (NULL);
	}
	while (++i < len1)
		str[i] = s1[i];
	while (++j < len2)
		str[i + j] = s2[j];
	str[i + j] = '\0';
	free(s1);
	return (str);
}

int	gnl_memchr(char *s, int c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

int	ft_shift(char *str, int i)
{
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*ft_overwrite(char *str)
{
	int		i;
	int		k;
	int		j;
	char	*rest;

	i = 0;
	k = 0;
	j = 0;
	if (str == NULL)
		return (ft_free(str));
	i = ft_shift(str, i);
	while (str[i + j] != '\0')
		j++;
	if (j == 0)
		return (ft_free(str));
	rest = malloc(j + 1);
	if (!rest)
		return (ft_free(str));
	while (str[i] != '\0')
		rest[k++] = str[i++];
	rest[k] = '\0';
	free(str);
	return (rest);
}
