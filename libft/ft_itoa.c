/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 10:19:57 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/05 11:35:56 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"
#include <limits.h>

static int	countlength(int n)
{
	int	length;

	length = 1;
	if (n < 0)
	{
		length++;
		n *= -1;
	}
	while (n)
	{
		n /= 10;
		length++;
	}
	return (length);
}

static void	transfer(char *out, int n, int length, int isminus)
{
	int	i;

	i = length - 2 + isminus;
	while (i >= 0)
	{
		out[i] = (n % 10) + '0';
		n /= 10;
		i--;
	}
}

static void	extracases(int isminus, int iszero, int isintmin, char *out)
{
	if (isminus == 1)
		out[0] = '-';
	if (iszero == 1)
		out[0] = '0';
	if (isintmin == 1)
		out[10] = '8';
}

static int	isminus_f(int n, int *isminus)
{
	if (n < 0)
	{
		*isminus = 1;
		n *= -1;
	}
	return (n);
}

char	*ft_itoa(int n)
{
	int		length;
	char	*out;
	int		isminus;
	int		iszero;
	int		isintmin;

	iszero = 0;
	isminus = 0;
	isintmin = 0;
	n = isminus_f(n, &isminus);
	if (n == 0)
		iszero = 1;
	if (n == INT_MIN)
	{
		n = INT_MAX;
		isintmin = 1;
	}
	length = countlength(n);
	out = ft_calloc(length + 1, sizeof(char));
	if (out == NULL)
		return (NULL);
	transfer(out, n, length, isminus);
	extracases(isminus, iszero, isintmin, out);
	return (out);
}
