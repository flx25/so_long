/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 14:08:04 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/08 09:52:01 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <unistd.h>
#include "libft.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
	i++;
	}
	return (i);
}

void	ft_putchar(char c, int *wlen)
{
	*wlen += write(1, &c, 1);
}

void	printstring(va_list *vl, int *wlen)
{
	char	*string;
	int		i;

	i = 0;
	string = va_arg(*vl, char *);
	if (!string)
		string = "(null)";
	while (i < ft_strlen(string))
	{
		*wlen += write(1, &string[i], 1);
		i++;
	}
}

void	format(char c, va_list *vl, int *wlen)
{
	if (c == 'c')
		ft_putchar(va_arg(*vl, int), wlen);
	if (c == 's')
		printstring(vl, wlen);
	if (c == 'i' || c == 'd')
		printint(va_arg(*vl, int), 1, wlen);
	if (c == 'p')
		printpointer(va_arg(*vl, void *), wlen);
	if (c == 'u')
		printunsignedint(va_arg(*vl, unsigned int), 1, wlen);
	if (c == 'x' || c == 'X')
		printhex(c, va_arg(*vl, unsigned int), wlen);
	if (c == '%')
		ft_putchar('%', wlen);
}

int	ft_printf(const char *fmt, ...)
{
	va_list	vl;
	int		i;
	int		wlen;

	wlen = 0;
	i = 0;
	va_start(vl, fmt);
	while (fmt && fmt[i])
	{
		if (fmt[i] == '%')
		{
			i++;
			format(fmt[i], &vl, &wlen);
		}
		else
		{
			wlen += write(1, &fmt[i], 1);
		}
		i++;
	}
	va_end(vl);
	return (wlen);
}
