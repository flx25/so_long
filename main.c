/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/15 09:06:07 by fvon-nag         ###   ########.fr       */
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
		move(0, -128, mega);
	if (keycode == 1)
		move(0, 128, mega);
	if (keycode == 0)
		move(-128, 0, mega);
	if (keycode == 2)
		move(128, 0, mega);
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

// void	mapcheck(char *map)
// {

// }

void	drawit(char c, int x, int y, t_mega *mega)
{
	static int	i;

	if (c == '1')
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[0].s_image.reference, x * 128, y * 128);
		mega[i].x = x * 128;
		mega[i].y = y * 128;
		mega[i].type = '1';
		i++;
	}
	if (c == '0')
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, x * 128, y * 128);
	if (c == 'P')
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, x * 128, y * 128);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[2].s_image.reference, x * 128, y * 128);
		mega[0].px = x * 128;
		mega[0].py = y * 128;
	}
	if (c == 'C')
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, x * 128, y * 128);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[4].s_image.reference, x * 128, y * 128);
		mega[0].needcoins += 1;
		mega[i].x = x * 128;
		mega[i].y = y * 128;
		mega[i].type = 'C';
		i++;
	}
	if (c == 'E')
	{
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[1].s_image.reference, x * 128, y * 128);
		mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
			mega[5].s_image.reference, x * 128, y * 128);
		mega[i].x = x * 128;
		mega[i].y = y * 128;
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
	//mapcheck(map);
	mapdraw(map, mega);

}

void initimages(t_mega **mega)
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

int ft_strlen_nnl(char *str)
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
	mega = initmap(argv[1]);
	mega[0].s_vars.mlx = mlx_init();
	mega[0].s_vars.win = mlx_new_window(mega[0].s_vars.mlx, 5400,
			3200, "so_long");
	initimages(&mega);
	mlx_key_hook(mega[0].s_vars.win, key, mega);
	usemap(argv[1], mega);
	mlx_hook(mega[0].s_vars.win, 17, 0, ft_close, mega);
	mlx_loop(mega[0].s_vars.mlx);
}
