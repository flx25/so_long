/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printunsignedint.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 14:05:11 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/08 09:52:39 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "libft.h"

static void	writedigits(unsigned int n, int fd, int *wlen)
{
	char	c;

	if (n >= 10)
	{
		writedigits(n / 10, fd, wlen);
		c = n % 10 + '0';
		*wlen += write(fd, &c, 1);
	}
	else
	{
		c = n + '0';
		*wlen += write(fd, &c, 1);
	}
}

void	printunsignedint(unsigned int n, int fd, int *wlen)
{
	if (n == 0)
	*wlen += write(fd, "0", 1);
	else
		writedigits(n, fd, wlen);
}
