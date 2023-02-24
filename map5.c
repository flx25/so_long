/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:15:05 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/24 08:18:04 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	rectch2(t_matrix **mapgr, int xmax, int ymax)
{
	int	i;

	i = 0;
	while (i < xmax)
	{
		if (mapgr[i][ymax - 1].c != '1')
			return (1);
	i++;
	}
	i = 0;
	while (i < ymax)
	{
		if (mapgr[xmax - 1][i].c != '1')
			return (1);
		i++;
	}
	i = 0;
	return (0);
}

int	rectch1(t_matrix **mapgr, int xmax, int ymax)
{
	int	i;

	i = 0;
	while (i < xmax)
	{
		if (mapgr[i][0].c != '1')
			return (1);
	i++;
	}
	i = 0;
	while (i < ymax)
	{
		if (mapgr[0][i].c != '1')
			return (1);
		i++;
	}
	i = 0;
	if (rectch2(mapgr, xmax, ymax) == 1)
		return (1);
	return (0);
}

int	ft_strlen_nnl(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != '\n' || str[i] != '0')
			count++;
		i++;
	}
	return (count);
}
