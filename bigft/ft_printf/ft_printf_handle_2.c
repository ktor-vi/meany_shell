/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_handle_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 08:45:22 by randre            #+#    #+#             */
/*   Updated: 2024/02/19 10:23:40 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <unistd.h>

int	ft_phandle(int fd, va_list args)
{
	size_t	nbr;

	nbr = va_arg(args, size_t);
	if (!nbr)
	{
		write(fd, "0x0", 3);
		return (3);
	}
	else
	{
		write(fd, "0x", 2);
		return (ft_hexa(fd, nbr, "0123456789abcdef") + 2);
	}
}
