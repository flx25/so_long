/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 14:54:26 by fvon-nag          #+#    #+#             */
/*   Updated: 2022/12/14 08:53:47 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t		i;

	i = 0;
	if (n == 0 || dest == NULL || src == NULL)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (src[i] != '\0' && (size_t) i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
		dest[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}
