/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: randre <randre@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 06:56:59 by randre            #+#    #+#             */
/*   Updated: 2024/02/19 10:32:10 by randre           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <stdarg.h>
# include "../libft/libft.h"

//unsigned int	ft_strlen(const char *str);
int				ft_printf(int fd, const char *str, ...);
int				ft_isvalid_arg(const char c);
int				ft_chandle(int fd, va_list args);
int				ft_shandle(int fd, va_list args);
int				ft_dhandle(int fd, va_list args);
int				ft_uhandle(int fd, va_list args);
int				ft_typecheck(int fd, const char c, va_list args);
int				ft_putnbr(int fd, int n);
int				ft_xhandle(int fd, va_list args, size_t i);
int				ft_xcount(int fd, size_t nbr);
int				ft_putnbr_long(int fd, unsigned int n);
int				ft_hexa(int fd, size_t nbr, char *base_str);
int				ft_phandle(int fd, va_list args);
int				ft_nbrlen(int nbr);

#endif
