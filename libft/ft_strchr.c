/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 09:07:12 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/27 13:54:16 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

char	*ft_strchr(const char *s, int i)
{
	int	j;

	j = 0;
	if (!s)
		return (NULL);
	if (i == '\0')
		return ((char *)&s[ft_strlen(s)]);
	while (s[j] != '\0')
	{
		if (s[j] == (char) i)
			return ((char *)&s[j]);
		j++;
	}
	return (NULL);
}
