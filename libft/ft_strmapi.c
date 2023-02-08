/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 13:19:38 by fvon-nag          #+#    #+#             */
/*   Updated: 2022/12/19 14:09:26 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned
				int, char))
{
	unsigned int	i;
	int				slen;
	char			*out;

	slen = ft_strlen(s);
	i = 0;
	out = ft_calloc(slen + 1, sizeof(char));
	if (out == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		out[i] = f(i, s[i]);
		i++;
	}
	return (out);
}
