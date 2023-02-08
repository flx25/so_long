/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:57:02 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/04 11:10:55 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

static int	findend(char const *s1, int *asciilist)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i > 0)
	{
		if (asciilist[(int)s1[i]] > 0)
			i--;
		else
			return (i);
	}
	return (i);
}

static void	setsetlength(char const *set, int *asciilist)
{
	int	i;
	int	setlength;

	i = 0;
	setlength = ft_strlen(set);
	while (i < setlength)
	{
		asciilist[(int)set[i]]++;
		i++;
	}
}

static char	*copyandtrim(char const *s1, char *out, int *asciilist, int end)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		if (asciilist[(int)s1[i]] > 0)
			i++;
		else
			break ;
	}
	while (s1[i] != '\0' && i <= end)
	{
		out[j] = s1[i];
		i++;
		j++;
	}
	return (out);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*out;
	int		asciilist[255];
	int		end;
	int		start;

	start = 0;
	ft_memset(asciilist, 0, sizeof(asciilist));
	setsetlength(set, asciilist);
	while (s1[start] != '\0')
	{
		if (asciilist[(int)s1[start]] > 0)
			start++;
		else
			break ;
	}
	end = findend(s1, asciilist);
	if (end == 0)
		out = (char *) ft_calloc(1, sizeof(char));
	else
		out = (char *) ft_calloc(end + 2 - start, sizeof(char));
	if (out == NULL)
		return (NULL);
	return (copyandtrim(s1, out, asciilist, end));
}
