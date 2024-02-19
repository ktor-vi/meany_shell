/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 06:18:54 by randre            #+#    #+#             */
/*   Updated: 2024/02/19 10:13:37 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int	ft_printf_loop(int fd, va_list args, const char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		if (*str != '%')
		{
			write(fd, str, 1);
			i++;
			str++;
		}
		else
		{
			str++;
			if (ft_isvalid_arg(*str) && *str != '%')
				i += ft_typecheck(fd, *str, args);
			else
			{
				write(fd, str, 1);
				i++;
			}
			str++;
		}
	}
	return (i);
}

int	ft_printf(int fd, const char *str, ...)
{
	va_list	args;
	int		i;

	if (!str)
		return (0);
	va_start(args, str);
	i = ft_printf_loop(fd, args, str);
	va_end(args);
	return (i);
}
