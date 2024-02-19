/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 06:55:36 by randre            #+#    #+#             */
/*   Updated: 2024/02/19 10:32:21 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int	ft_putnbr(int fd, int n)
{
	char	c;
	int		i;

	i = ft_nbrlen(n);
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return (11);
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n = -n;
		i++;
	}
	if (n > 9)
	{
		ft_putnbr(fd, n / 10);
		ft_putnbr(fd, n % 10);
	}
	c = (char)(n + 48);
	if (n < 10)
		write(fd, &c, 1);
	return (i);
}

/*unsigned int	ft_strlen(const char *str)
{
	unsigned int	i;

	i = 0;
	if (!str)
		return (0);
	while (*str)
	{
		i++;
		str++;
	}
	return (i);
}*/

int	ft_isvalid_arg(const char c)
{
	if (c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i'
		|| c == 'u' || c == 'x' || c == 'X' || c == '%')
		return (1);
	else
		return (0);
}

int	ft_typecheck(int fd, const char c, va_list args)
{
	if (c == 'c')
		return (ft_chandle(fd, args));
	else if (c == 's')
		return (ft_shandle(fd, args));
	else if (c == 'p')
		return (ft_phandle(fd, args));
	else if (c == 'd')
		return (ft_dhandle(fd, args));
	else if (c == 'i')
		return (ft_dhandle(fd, args));
	else if (c == 'u')
		return (ft_uhandle(fd, args));
	else if (c == 'x')
		return (ft_xhandle(fd, args, 0));
	else if (c == 'X')
		return (ft_xhandle(fd, args, 1));
	return (0);
}
