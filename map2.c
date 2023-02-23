/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:07:07 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/23 18:09:42 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	mapdrawch(char *map, t_matrix **mapgr)
{
	int	i;
	int	x;
	int	y;

	x = 0;
	i = 0;
	y = 0;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
		{
			x = 0;
			y++;
		}
		else
		{
			mapgr[x][y].c = map[i];
			x++;
		}
		i++;
	}
}

int	*mapsize(char *map)
{
	int	*xy;
	int	i;

	xy = ft_calloc(3, sizeof(int));
	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] != '\n')
			xy[0]++;
		else
		{
			xy[1]++;
			xy[0] = 0;
		}
		i++;
	}
	xy[1]++;
	return (xy);
}

t_matrix	**allocmapsize(char *map)
{
	t_matrix	**mapgr;
	t_matrix	*data;
	int			*msize;
	int			i;

	msize = mapsize(map);
	data = ft_calloc(msize[0] * msize[1], sizeof(t_matrix));
	mapgr = ft_calloc(msize[0], sizeof(t_matrix *));
	i = 0;
	while (i < msize[0])
	{
		mapgr[i] = data + i * msize[1];
		i++;
	}
	free(msize);
	return (mapgr);
}

int	pathcheck(char *argv1)
{
	char		*map;
	t_matrix	**mapgr;
	int			*player;
	int			error;
	int			*mapsizei;

	error = 0;
	map = readmap(argv1);
	mapgr = allocmapsize(map);
	mapdrawch(map, mapgr);
	mapsizei = mapsize(map);
	player = givep(mapgr, mapsizei[0]);
	DFS(mapgr, player[0], player[1]);
	error = checkpath(mapgr, mapsizei[0], mapsizei[1]);
	free(player);
	free(mapsizei);
	free(mapgr[0]);
	free(mapgr);
	free(map);
	return (error);
}

int	checkrect(char *argv1)
{
	char		*map;
	t_matrix	**mapgr;
	int			error;
	int			*mapsizei;

	error = 0;
	map = readmap(argv1);
	mapgr = allocmapsize(map);
	mapdrawch(map, mapgr);
	mapsizei = mapsize(map);
	error = rectch1(mapgr, mapsizei[0], mapsizei[1]);
	free(map);
	free(mapgr[0]);
	free(mapgr);
	free(mapsizei);
	if (error != 0)
		ft_printf("Error\nMap needs to be rectangular, surrounded by walls!\n");
	return (error);
}
