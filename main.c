/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/10 11:50:36 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// WATCH OUT COMPILER FLAGS OFF
// t_image	ft_new_sprite(void *mlx, char *path)
// {
// 	t_image	img;

// 	img.pointer = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
// 	img.pixels  = mlx_get_data_addr(img.reference, &img.bits_per_pixel, &img.line_size, &img.endian);
// 	return (img);
// }

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
		mlx_destroy_window(vars->mlx, vars->win);

	// maybe need more to close

	return (0);
}
void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	main(void)
{
	t_data	img;
	t_vars	vars;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 640, 480, "Hello world!");
	mlx_key_hook(vars.win, key, &vars);
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
	 		&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 17, 0, close, &vars);
	mlx_loop(vars.mlx);
	// mlx_key_hook(vars.win, key, &vars);
	// mlx_loop(vars.mlx);
	// mlx_loop(mlx);
}
