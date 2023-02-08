/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 15:15:51 by fvon-nag          #+#    #+#             */
/*   Updated: 2022/12/17 13:07:06 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t			i;
	unsigned char	*out;

	if ((nmemb >= __SIZE_MAX__ && size >= __SIZE_MAX__))
		return (NULL);
	out = (unsigned char *) malloc(nmemb * size);
	if (out == NULL)
		return (NULL);
	i = 0;
	while (i < nmemb * size)
	{
		out[i] = 0;
		i++;
	}
	return (out);
}
