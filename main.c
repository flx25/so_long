/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/20 10:33:00 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// CHECK FOR LEAKS
// debugging flags on
// may other flags off
// need to find some way to work with big maps
//maybe make window size depended on map rows and collums

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
		//some kind of winning function
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[6].s_image.reference, mega[0].px, mega[0].py);
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
		mlx_destroy_window(mega[0].s_vars.mlx, mega[0].s_vars.win);
		exit(0);
			// maybe need more to close
	}

	return (0);
}

int	ft_close(void)
{
	exit(0);
}

// void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int *)dst = color;
// }

char	*readmap(char *map)
{
	int		fd;
	char	*temp;
	char	*out;

	temp = ft_calloc(1, sizeof(char));
	out = ft_calloc(1, sizeof(char));
	fd = open(map, O_RDONLY);
	while (temp)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			break ;
		out = ft_gnl_strjoin(out, temp);
	}
	free(temp);
	return (out);
}

int	*mapsize (char *map)
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
char	**allocmapsize(char *map)
{
	char	**mapgr;
	char	*data;
	int		x;
	int		y;
	int		i;

	x = mapsize(map)[0];
	y = mapsize(map)[1];
	data = ft_calloc(x * y, sizeof(char));
	mapgr = ft_calloc(x, sizeof(char *));
	i = 0;
	while (i < x)
	{
		mapgr[i] = data + i * y;
		i++;
	}
	return (mapgr);
}
void mapdrawch(char *map, char **mapgr)
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
			mapgr[x][y] = map[i];
		i++;
		x++;
	}
}

void	mapcheck(char *argv1)
{
	char	*map;
	char	**mapgr;

	map = readmap(argv1);
	mapgr = allocmapsize(map);
	mapdrawch(map, mapgr);
	//free(mapgr[0]); // Free the memory block pointed to by the first pointer in mapgr
	//free(mapgr);
}

void	drawit(char c, int x, int y, t_mega *mega)
{
	static int	i;

	if (c == '1')
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[0].s_image.reference, x * mega[0].is, y * mega[0].is);
		mega[i].x = x * mega[0].is;
		mega[i].y = y * mega[0].is;
		mega[i].type = '1';
		i++;
	}
	if (c == '0')
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, x * mega[0].is, y * mega[0].is);
	if (c == 'P')
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, x * mega[0].is, y * mega[0].is);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[2].s_image.reference, x * mega[0].is, y * mega[0].is);
		mega[0].px = x * mega[0].is;
		mega[0].py = y * mega[0].is;
	}
	if (c == 'C')
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, x * mega[0].is, y * mega[0].is);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[4].s_image.reference, x * mega[0].is, y * mega[0].is);
		mega[0].needcoins += 1;
		mega[i].x = x * mega[0].is;
		mega[i].y = y * mega[0].is;
		mega[i].type = 'C';
		i++;
	}
	if (c == 'E')
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, x * mega[0].is, y * mega[0].is);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[5].s_image.reference, x * mega[0].is, y * mega[0].is);
		mega[i].x = x * mega[0].is;
		mega[i].y = y * mega[0].is;
		mega[i].type = 'E';
		i++;
	}


}

void mapdraw(char *map, t_mega *mega)
{
	int	i;
	int	x;
	int	y;

	x = 1;
	i = 0;
	y = 1;
	while (map[i] != '\0')
	{
		if (map[i] == '\n')
		{
			x = 0;
			y++;
		}
		else
			drawit(map[i], x, y, mega);
		i++;
		x++;
	}
}

void	usemap(char *arg1, t_mega *mega)
{
	char	*map;

	ft_printf("%s \n", map = readmap(arg1));
	mapdraw(map, mega);

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

void	initimagessm(t_mega **mega) //sm = 24
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
			"winning.xpm");
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

t_mega	*initmap(char *argv1)
{
	char	*map;
	int		msize;
	int		i;
	t_mega	*out;

	map = readmap(argv1);
	msize = ft_strlen_nnl(map);
	i = 0;

	out = (t_mega *) ft_calloc(msize + 1, sizeof(t_mega));

	// while (i <= msize)
	// {
	// 	out[i] = (t_mega *) ft_calloc(1, sizeof(t_mega));
	// 	i++;
	// }
	out[0].structlen = msize;
	free(map);
	return (out);
}

int	main(int argc, char **argv)
{
	t_mega	*mega;

	if (argc != 2)
		return (ft_printf("Please give a map as an argument!\n"));
	mapcheck(argv[1]);
	mega = initmap(argv[1]);
	mega[0].s_vars.mlx = mlx_init();
	mega[0].s_vars.win = mlx_new_window(mega[0].s_vars.mlx, 5400,
			3200, "so_long");
	mega[0].is = 128;
	if (mega[0].is == 128)
		initimages(&mega);
	else
		initimagessm(&mega);
	mlx_key_hook(mega[0].s_vars.win, key, mega);
	usemap(argv[1], mega);
	mlx_hook(mega[0].s_vars.win, 17, 0, ft_close, mega);
	mlx_loop(mega[0].s_vars.mlx);
}
