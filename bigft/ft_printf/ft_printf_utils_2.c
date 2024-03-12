/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:41:43 by randre            #+#    #+#             */
/*   Updated: 2024/02/19 10:25:11 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"
#include <stdlib.h>

int	ft_nbrlen(int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		i++;
		nbr /= 10;
	}
	return (i);
}

int	ft_nbrlenlong(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		i++;
		nbr /= 10;
	}
	return (i);
}

int	ft_xcount(int fd, size_t nbr)
{
	int	y;

	y = 0;
	if (nbr == 0)
	{
		write(fd, "0", 1);
		return (-1);
	}
	while (nbr != 0)
	{
		y++;
		nbr /= 16;
	}
	return (y);
}

int	ft_putnbr_long(int fd, unsigned int n)
{
	char	c;

	if (n > 9)
	{
		ft_putnbr_long(fd, n / 10);
		ft_putnbr_long(fd, n % 10);
	}
	c = (char)(n + 48);
	if (n < 10)
		write(fd, &c, 1);
	return (ft_nbrlenlong(n));
}

int	ft_hexa(int fd, size_t nbr, char *base_str)
{
	int		y;
	char	*str;
	int		i;

	i = ft_xcount(fd, nbr);
	if (i == -1)
		return (1);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (0);
	y = -1;
	while (y++ < i)
		str[y] = '0';
	str[i] = 0;
	y = i - 1;
	while (y > -1)
	{
		str[y] = base_str[nbr % 16];
		nbr /= 16;
		y--;
	}
	write(fd, str, i);
	free(str);
	return (i);
}
