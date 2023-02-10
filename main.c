/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/10 14:59:24 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// CHECK FOR LEAKS
// debugging flags on

int	key(int keycode, t_vars *vars)
{
	if (keycode == 13)
		ft_printf("UP (W)\n");
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
	fd = open(map, O_RDONLY);
	while (temp)
	{
		temp = get_next_line(fd);
		out = ft_gnl_strjoin(out, temp);
	}
	free(temp);
	return (out);
}

void	usemap(char *arg1)
{
	ft_printf("the map name is %s", arg1);
	readmap(arg1);
}

int	main(int argc, char **argv)
{
	t_data	img;
	t_vars	vars;

	if (argc != 2)
		return (ft_printf("Please give a map as an argument!\n"));
	usemap(argv[1]);
	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "so_long");
	mlx_key_hook(vars.win, key, &vars);
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 17, 0, ft_close, &vars);
	mlx_loop(vars.mlx);
}
