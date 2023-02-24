/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:18:16 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/24 16:18:30 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	drawitpre(char c, int x, int y, t_mega *mega)
{
	static int	i;
	t_vector	xy;

	xy.x = x;
	xy.y = y;
	if (c == 'C' || c == 'E')
		drawit2(c, xy, mega, &i);
	else
		drawit1(c, xy, mega, &i);
}

void	drawit1(char c, t_vector xy, t_mega *mega, int *i)
{
	if (c == '1')
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[0].s_image.reference, xy.x * mega[0].is, xy.y * mega[0].is);
		mega[*i].x = xy.x * mega[0].is;
		mega[*i].y = xy.y * mega[0].is;
		mega[*i].type = '1';
		(*i)++;
	}
	if (c == '0')
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, xy.x * mega[0].is, xy.y * mega[0].is);
	if (c == 'P')
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, xy.x * mega[0].is, xy.y * mega[0].is);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[2].s_image.reference, xy.x * mega[0].is, xy.y * mega[0].is);
		mega[0].px = xy.x * mega[0].is;
		mega[0].py = xy.y * mega[0].is;
	}
}

void	drawit2(char c, t_vector xy, t_mega *mega, int *i)
{
	if (c == 'C')
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, xy.x * mega[0].is, xy.y * mega[0].is);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[4].s_image.reference, xy.x * mega[0].is, xy.y * mega[0].is);
		mega[0].needcoins += 1;
		mega[*i].x = xy.x * mega[0].is;
		mega[*i].y = xy.y * mega[0].is;
		mega[*i].type = 'C';
		(*i)++;
	}
	if (c == 'E')
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, xy.x * mega[0].is, xy.y * mega[0].is);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[5].s_image.reference, xy.x * mega[0].is, xy.y * mega[0].is);
		mega[*i].x = xy.x * mega[0].is;
		mega[*i].y = xy.y * mega[0].is;
		mega[*i].type = 'E';
		(*i)++;
	}
}

void	mapdraw(char *map, t_mega *mega)
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
			drawitpre(map[i], x, y, mega);
			x++;
		}
	i++;
	}
}

void	usemap(char *arg1, t_mega *mega)
{
	char	*map;

	ft_printf("%s \n", map = readmap(arg1));
	mapdraw(map, mega);
	free(map);
}
