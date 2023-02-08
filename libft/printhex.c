/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printhex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 15:47:47 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/08 09:52:44 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	writedigitslowc(unsigned long n, int fd, int *wlen)
{
	char	c;

	if (n >= 16)
	{
		writedigitslowc(n / 16, fd, wlen);
		writedigitslowc(n % 16, fd, wlen);
	}
	else
	{
		c = "0123456789abcdef"[n % 16];
		*wlen += write(fd, &c, 1);
	}
}

static void	writedigitsupc(unsigned long n, int fd, int *wlen)
{
	char	c;

	if (n >= 16)
	{
		writedigitsupc(n / 16, fd, wlen);
		writedigitsupc(n % 16, fd, wlen);
	}
	else
	{
		c = "0123456789ABCDEF"[n % 16];
		*wlen += write(fd, &c, 1);
	}
}

void	printhex(char c, unsigned int hex, int *wlen)
{
	if (c == 'X')
		writedigitsupc((unsigned long) hex, 1, wlen);
	if (c == 'x')
		writedigitslowc((unsigned long) hex, 1, wlen);
}
