/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:27:41 by fvon-nag          #+#    #+#             */
/*   Updated: 2022/12/19 10:18:00 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "libft.h"

static char	*transfer(char const *s, unsigned int start, size_t len, char *out)
{
	unsigned int	i;
	unsigned int	c;
	unsigned int	slength;

	c = 0;
	i = start;
	slength = (unsigned int) ft_strlen(s);
	while (s[i] != '\0' && i - start < len
		&& start <= slength)
	{
		out[c] = s[i];
		i++;
		c++;
	}
	return (out);
}

char	*ft_substr(char const *s, unsigned int start,
			size_t len)
{
	char			*out;
	unsigned int	i;
	unsigned int	c;
	unsigned int	slength;

	c = 0;
	i = start;
	slength = (unsigned int) ft_strlen(s);
	if (slength < start)
	{
		out = ft_calloc(1, sizeof(char));
		return (out);
	}
	else if (len > slength)
		out = ft_calloc(slength + 1, sizeof(char));
	else
		out = ft_calloc(len + 1, sizeof(char));
	if (out == NULL)
		return (NULL);
	return (transfer(s, start, len, out));
}
