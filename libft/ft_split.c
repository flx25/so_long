/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 10:55:55 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/05 13:33:30 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	splitcount(char const *s, char c, int *countnc)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			count++;
		else if (s[i] != c && s[i + 1] != c)
			(*countnc)++;
		i++;
	}
	return (count);
}

static void	lengthcount(char const *s, char c, int *lenlist)
{
	int	i;
	int	countnc;
	int	y;
	int	slength;

	slength = ft_strlen(s);
	y = 0;
	i = 0;
	countnc = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
			countnc++;
		if ((i > 0 && (s[i] == c || i == slength - 1) && s[i - 1] != c))
		{
			lenlist[y] = countnc;
			y++;
			countnc = 0;
		}
		i++;
	}
}

static char	**transfer(char const *s, char c, char **out)
{
	int	i;
	int	j;
	int	y;

	i = 0;
	j = 0;
	y = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] != c)
		{
		out[y][j] = s[i];
		i++;
		j++;
		}
		while (s[i] != '\0' && s[i] == c && i > 0 && s[i - 1] != c)
		{
			j = 0;
			y++;
			i++;
		}
		while ((s[i] == c && i == 0) || (s[i] == c && s[i - 1] == c))
			i++;
	}
	return (out);
}

char	**ft_split(char const *s, char c)
{
	int		y;
	int		count;
	char	**out;
	int		*lenlist;
	int		countnc;

	countnc = 0;
	count = splitcount(s, c, &countnc);
	if (count == 0 && countnc > 0)
		count = 1;
	out = (char **) ft_calloc((count + 1), sizeof(char *));
	if (out == NULL)
		return (NULL);
	lenlist = malloc((count) * sizeof(int));
	lengthcount(s, c, lenlist);
	y = 0;
	while (y < count)
	{
		out[y] = (char *) ft_calloc(lenlist[y] + 1, sizeof(char));
		y++;
	}
	free(lenlist);
	return (transfer(s, c, out));
}
