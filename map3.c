/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:13:11 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/23 18:40:56 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	dfs(t_matrix **mapgr, int x, int y)
{
	mapgr[x][y].v = true;
	if (mapgr[x + 1][y].c != '1' && mapgr[x + 1][y].v != 1)
		dfs(mapgr, x + 1, y);
	if (mapgr[x][y + 1].c != '1' && mapgr[x][y + 1].v != 1)
		dfs(mapgr, x, y + 1);
	if (mapgr[x - 1][y].c != '1' && mapgr[x - 1][y].v != 1)
		dfs(mapgr, x - 1, y);
	if (mapgr[x][y - 1].c != '1' && mapgr[x][y - 1].v != 1)
		dfs(mapgr, x, y - 1);
}

int	*givep(t_matrix **mapgr, int xsize)
{
	int	x;
	int	y;
	int	*out;

	out = ft_calloc(3, sizeof(int));
	x = 0;
	y = 0;
	while (mapgr[x][y].c != '\0')
	{
		while (x < xsize)
		{
			if (mapgr[x][y].c == 'P')
			{
				out[0] = x;
				out[1] = y;
				return (out);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (NULL);
}

int	checkpath(t_matrix **mapgr, int xsize, int ysize)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < ysize)
	{
		while (x < xsize)
		{
			if ((mapgr[x][y].c == 'P' || mapgr[x][y].c == 'E'
				|| mapgr[x][y].c == 'C') && mapgr[x][y].v == 0)
			{
				ft_printf("Error\nNo valid path on the map!\n");
				return (1);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (0);
}

int	checkmin(char *map)
{
	int	i;
	int	p;
	int	c;
	int	e;

	e = 0;
	i = 0;
	p = 0;
	c = 0;
	while (map[i] != '\0')
	{
		if (map[i] == 'P')
			p++;
		if (map[i] == 'E')
			e++;
		if (map[i] == 'C')
			c++;
	i++;
	}
	if (p != 1 || c < 1 || e != 1)
		return (ft_printf("Error\nMap needs 1 E, 1 P and at least 1 C!\n"), 1);
	else
		return (0);
}

int	checkchars(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] != '\n' && map[i] != '1' && map[i] != '0'
			&& map[i] != 'P' && map[i] != 'E' && map[i] != 'C')
		{
			ft_printf("Error\nForbidden characters!");
			return (1);
		}
		i++;
	}
	return (0);
}
