/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vphilipp <vphilipp@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 11:44:52 by vphilipp          #+#    #+#             */
/*   Updated: 2023/10/30 16:25:39 by vphilipp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 41
# endif

char	*get_next_line(int fd);
size_t	gnl_strlen(char *str);
void	*ft_memmove(void *dst, void *src, size_t len);
char	*gnl_strjoin(char *s1, char *s2);
int		gnl_memchr(char *s, int c);
char	*ft_overwrite(char *str);
char	*ft_free(char *str);

#endif
