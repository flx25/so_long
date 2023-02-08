/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printpointer.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:35:40 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/08 09:52:35 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

static void	writedigits(unsigned long n, int fd, int *wlen)
{
	char	c;

	if (n >= 16)
	{
		writedigits(n / 16, fd, wlen);
		writedigits(n % 16, fd, wlen);
	}
	else
	{
		c = "0123456789abcdef"[n % 16];
		*wlen += write(fd, &c, 1);
	}
}

void	printpointer(void *ptr, int *wlen)
{
	*wlen += write(1, "0x", 2);
	writedigits((unsigned long) ptr, 1, wlen);
}
