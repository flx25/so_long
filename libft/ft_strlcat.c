/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 11:15:51 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/05 14:49:40 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	srclength;
	size_t	i;
	size_t	dstlength;

	srclength = ft_strlen(src);
	dstlength = ft_strlen(dst);
	i = 0;
	if (size == 0)
		return (srclength);
	if (size < dstlength)
		return (size + srclength);
	while (i < srclength && i + dstlength < size - 1)
	{
		dst[dstlength + i] = src[i];
		i++;
	}
	dst[dstlength + i] = '\0';
	return (dstlength + srclength);
}
