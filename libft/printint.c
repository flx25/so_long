/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 10:25:18 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/08 09:52:30 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>
#include "libft.h"

static void	writedigits(int n, int fd, int *wlen)
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

void	printint(int n, int fd, int *wlen)
{
	char	minus;

	minus = '-';
	if (n == -2147483648)
	*wlen += write(fd, "-2147483648", 11);
	else if (n == 0)
	*wlen += write(fd, "0", 1);
	else if (n < 0)
	{
		*wlen += write(fd, &minus, 1);
		writedigits(n * -1, fd, wlen);
	}
	else
		writedigits(n, fd, wlen);
}
