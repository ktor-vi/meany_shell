/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handle_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 07:33:11 by randre            #+#    #+#             */
/*   Updated: 2024/02/19 10:23:26 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_chandle(int fd, va_list args)
{
	char	c;

	c = (char) va_arg(args, int);
	write(fd, &c, 1);
	return (1);
}

int	ft_shandle(int fd, va_list args)
{
	char	*str;

	str = va_arg(args, char *);
	if (!str)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	else
	{
		write(fd, str, ft_strlen(str));
		return (ft_strlen(str));
	}
}

int	ft_dhandle(int fd, va_list args)
{
	int	nbr;

	nbr = va_arg(args, int);
	return (ft_putnbr(fd, nbr));
}

int	ft_uhandle(int fd, va_list args)
{
	unsigned int	nbrr;

	nbrr = va_arg(args, unsigned int);
	return (ft_putnbr_long(fd, nbrr));
}

int	ft_xhandle(int fd, va_list args, size_t i)
{
	unsigned int	nbr;

	nbr = va_arg(args, unsigned int);
	if (i == 0)
		return (ft_hexa(fd, nbr, "0123456789abcdef"));
	else
		return (ft_hexa(fd, nbr, "0123456789ABCDEF"));
}
