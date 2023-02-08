/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 08:27:48 by fvon-nag          #+#    #+#             */
/*   Updated: 2022/12/15 13:13:54 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char	*haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		c;

	i = 0;
	if (len == 0 && needle[0] != '\0')
		return (0);
	if (needle[0] == '\0' || len == 0)
		return ((char *) haystack);
	while (haystack[i] != '\0' && i < len)
	{
		c = 0;
		while (haystack[i + c] != '\0' && haystack[i + c] == needle[c]
			&& i + c < len)
		{
			if (needle[c + 1] == '\0')
				return ((char *)&haystack[i]);
			c++;
		}
		i++;
	}
	return (0);
}
