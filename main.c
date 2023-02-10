/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/10 17:49:04 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// CHECK FOR LEAKS
// debugging flags on
// may other flags off

struct s_vector g_player;

t_image	ft_new_sprite(void *mlx, char *path)
{
	t_image	img;

	img.pointer = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
	img.pixels = mlx_get_data_addr(img.pointer, &img.bits_per_pixel,
			&img.line_size, &img.endian);
	return (img);
}

void move(int x, int y, t_vars *vars, t_image *img)
{
	mlx_put_image_to_window(vars->mlx, vars->win, img[2].pointer,
		g_player.x, g_player.y);
	mlx_put_image_to_window(vars->mlx, vars->win, img[2].pointer,
		g_player.x + x, g_player.y + y);

	g_player.x += x;
	g_player.y += y;

}
int	key(int keycode, t_vars *vars, t_image *img)
{
	if (keycode == 13)
		move(0, 128, vars, img);
	if (keycode == 1)
		ft_printf("DOWN (S)\n");
	if (keycode == 0)
		ft_printf("LEFT (A)\n");
	if (keycode == 2)
		ft_printf("RIGHT (D)\n");
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	// maybe need more to close
	return (0);
}

int	ft_close(void)
{
	exit(0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

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

void	mapcheck(char *map)
{

}

void	drawit(char c, t_image *img, int x, int y, t_vars vars)
{
	if (c == '1')
		mlx_put_image_to_window(vars.mlx, vars.win, img[0].pointer,
			x * 128, y * 128);
	if (c == '0')
		mlx_put_image_to_window(vars.mlx, vars.win, img[1].pointer,
			x * 128, y * 128);
	if (c == 'E')
	{
		mlx_put_image_to_window(vars.mlx, vars.win, img[2].pointer,
			x * 128, y * 128);
		g_player.x = x * 128;
		g_player.y = y * 128;
	}


}

void mapdraw(char *map, t_image *img, t_vars vars)
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
			drawit(map[i], img, x, y, vars);
		i++;
		x++;
	}
}

void	usemap(char *arg1, t_image *img, t_vars vars)
{
	char	*map;

	ft_printf("%s \n", map = readmap(arg1));
	//mapcheck(map);
	mapdraw(map, img, vars);

}

t_image	*initimages(t_vars vars)
{
	t_image	*img;

	img = ft_calloc(3 + 1, sizeof(t_image));
	img[0] = ft_new_sprite(vars.mlx, "Bricks_11-128x128.xpm");
	img[1] = ft_new_sprite(vars.mlx, "Tile_14-128x128.xpm");
	img[2] = ft_new_sprite(vars.mlx, "Ghost.xpm");


	return (img);
}

int	main(int argc, char **argv)
{
	t_image	*img;
	t_vars	vars;

	if (argc != 2)
		return (ft_printf("Please give a map as an argument!\n"));

	// maybe ** make all image pointers in the beginning
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 2400, 1200, "so_long");
	img = initimages(vars);
	mlx_key_hook(vars.win, key, &vars);
	usemap(argv[1], img, vars);

	//mlx_put_image_to_window(vars.mlx, vars.win, img[0].pointer, 0, 0);
	//mlx_put_image_to_window(vars.mlx, vars.win, img[0].pointer, 200, 200);
	mlx_hook(vars.win, 17, 0, ft_close, &vars);
	mlx_loop(vars.mlx);
}
