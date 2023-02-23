/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/23 18:40:49 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// CHECK FOR LEAKS -> ask about the issue with the destroy images
// debugging flags on
// may other flags off
// try different kind of frees in the gnl strjoin function -> leaks

t_image	ft_new_sprite(void *mlx, char *path)
{
	t_image	img;

	img.reference = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
	img.pixels = mlx_get_data_addr(img.reference, &img.bits_per_pixel,
			&img.line_size, &img.endian);
	return (img);
}

int	tilecheck(int x, int y, t_mega *mega)
{
	int	i;

	i = 0;
	while (i <= mega[0].structlen)
	{
		if (mega[i].x == x && mega[i].y == y)
			return (i);
		i++;
	}
	return (-1);
}

void	destroyimages(t_mega **mega)
{
	mlx_destroy_image(mega[0]->s_vars.mlx, mega[0]->s_image.reference);
	mlx_destroy_image(mega[0]->s_vars.mlx, mega[1]->s_image.reference);
	mlx_destroy_image(mega[0]->s_vars.mlx, mega[2]->s_image.reference);
	mlx_destroy_image(mega[0]->s_vars.mlx, mega[3]->s_image.reference);
	mlx_destroy_image(mega[0]->s_vars.mlx, mega[4]->s_image.reference);
	mlx_destroy_image(mega[0]->s_vars.mlx, mega[5]->s_image.reference);
	mlx_destroy_image(mega[0]->s_vars.mlx, mega[6]->s_image.reference);
}

int	ft_close(t_mega *mega)
{
	destroyimages(&mega);
	mlx_destroy_window(mega[0].s_vars.mlx, mega[0].s_vars.win);
	free(mega);
	//exit(0);
	return (0);
}

void move(int x, int y, t_mega *mega)
{
	int	tcret;

	tcret = tilecheck(mega[0].px + x, mega[0].py + y, mega);
	if (tcret == -1)
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[3].s_image.reference, mega[0].px, mega[0].py);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, mega[0].px, mega[0].py);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[2].s_image.reference, mega[0].px + x, mega[0].py + y);
		mega[0].px = mega[0].px + x;
		mega[0].py = mega[0].py + y;
		mega[0].stepsdone += 1;
	}
	else if (mega[tcret].type == 'C' )
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[3].s_image.reference, mega[0].px, mega[0].py);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, mega[0].px, mega[0].py);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[2].s_image.reference, mega[0].px + x, mega[0].py + y);
		mega[0].px = mega[0].px + x;
		mega[0].py = mega[0].py + y;
		mega[0].stepsdone += 1;
		if (mega[tcret].collected == 0)
		{
			mega[0].colcoins += 1;
			mega[tcret].collected = 1;
		}
	}
	else if (mega[tcret].type == 'E' && mega[0].colcoins == mega[0].needcoins)
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[3].s_image.reference, mega[0].px, mega[0].py);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, mega[0].px, mega[0].py);
		mega[0].px = mega[0].px + x;
		mega[0].py = mega[0].py + y;
		mega[0].stepsdone += 1;
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[6].s_image.reference, mega[0].px, mega[0].py);
		ft_close(mega);
	}
	ft_printf("steps done: %i\n", mega[0].stepsdone);
}

int	key(int keycode, t_mega *mega)
{
	if (keycode == 13)
		move(0, -mega[0].is, mega);
	if (keycode == 1)
		move(0, mega[0].is, mega);
	if (keycode == 0)
		move(-mega[0].is, 0, mega);
	if (keycode == 2)
		move(mega[0].is, 0, mega);
	if (keycode == 53)
	{
		destroyimages(&mega);
		mlx_destroy_window(mega[0].s_vars.mlx, mega[0].s_vars.win);
		free(mega);
		//exit(0);
	}
	return (0);
}

void	initimages(t_mega **mega)
{
	(*mega)[0].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"Bricks_14-128x128.xpm");
	(*mega)[1].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"Tile_14-128x128.xpm");
	(*mega)[2].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"Ghost.xpm");
	(*mega)[3].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"black.xpm");
	(*mega)[4].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"collect.xpm");
	(*mega)[5].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"ladder.xpm");
	(*mega)[6].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"winning.xpm");
}

void	initimagessm(t_mega **mega)
{
	(*mega)[0].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"small/Bricks_14_s.xpm");
	(*mega)[1].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"small/tile14_s.xpm");
	(*mega)[2].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"small/Ghost_s.xpm");
	(*mega)[3].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"small/Black_s.xpm");
	(*mega)[4].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"small/Coll_s.xpm");
	(*mega)[5].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"small/ladder_s.xpm");
	(*mega)[6].s_image = ft_new_sprite(mega[0]->s_vars.mlx,
			"small/winning_s.xpm");
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


void	initwindow(t_mega **mega, char *argv1)
{
	char	*map;
	int		*msize;

	map = readmap(argv1);
	msize = mapsize(map);
	(*mega)[0].msize = msize; //remember to free
	if (mega[0]->msize[0] * 128 <= 2560 && mega[0]->msize[1] * 128 <= 1400)
		(*mega)[0].is = 128;
	else
		(*mega)[0].is = 24;
	(*mega)[0].s_vars.mlx = mlx_init();
	(*mega)[0].s_vars.win = mlx_new_window(mega[0]->s_vars.mlx, mega[0]->is
			* mega[0]->msize[0], mega[0]->is * mega[0]->msize[1], "so_long");
	if (mega[0]->is == 128)
		initimages(mega);
	else
		initimagessm(mega);
	free(msize);
	free(map);
}


int rectch2(t_matrix **mapgr, int xmax, int ymax)
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

int rectch1(t_matrix **mapgr, int xmax, int ymax)
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

int	main(int argc, char **argv)
{
	t_mega	*mega;

	if (argc != 2)
		return (ft_printf("Error\nPlease give a map as an argument!\n"));
	if (checks(argv[1]) != 0)
		exit(0); // maybe need to free more
	mega = initmap(argv[1]);
	initwindow(&mega, argv[1]);
	mlx_key_hook(mega[0].s_vars.win, key, mega);
	usemap(argv[1], mega);
	mlx_hook(mega[0].s_vars.win, 17, 0, ft_close, mega);
	mlx_loop(mega[0].s_vars.mlx);
	destroyimages(&mega);
	mlx_destroy_window(mega[0].s_vars.mlx, mega[0].s_vars.win);
	free(mega);
	//mlx_destroy_display(mega[0].s_vars.mlx);
	//destroy images
	// get library with destroy images
	//use leaks
	// leaks --atExit -- ./so_long ...
}
