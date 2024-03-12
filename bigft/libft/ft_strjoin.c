/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 13:34:49 by vphilipp          #+#    #+#             */
/*   Updated: 2023/10/25 16:31:53 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>

static size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	i;

	joined = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (joined == NULL)
		return (NULL);
	i = -1;
	while (++i < ft_strlen(s1))
		joined[i] = s1[i];
	i = -1;
	while (++i < ft_strlen(s2))
		joined[i + ft_strlen(s1)] = s2[i];
	joined[i + ft_strlen(s1)] = '\0';
	return (joined);
}
//
// #include <stdio.h>
//
// int main(int argc, char **argv)
// {
//   argc = 0;
//   printf("%s", ft_strjoin(argv[1], argv[2]));
// }
