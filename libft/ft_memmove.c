/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 09:14:48 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/04 12:00:33 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int		i;
	char	*csrc;
	char	*cdest;

	if (src == NULL && n != 0 && dest == 0)
		return (NULL);
	csrc = (char *) src;
	cdest = (char *) dest;
	i = 0;
	if (dest < src)
	{
		ft_memcpy(dest, src, n);
		return (dest);
	}
		i = n - 1;
	while (i >= 0)
	{
			cdest[i] = csrc[i];
			i--;
	}
	return (dest);
}
