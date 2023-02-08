/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:09:03 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/05 11:32:42 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ps;
	unsigned char	*pd;

	if (src == NULL && n != 0 && dest == 0)
		return (NULL);
	ps = (unsigned char *) src;
	pd = dest;
	while (n--)
	{
		*pd++ = (unsigned char) *ps++;
	}
	return (dest);
}
