/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/09 11:21:43 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// t_image	ft_new_sprite(void *mlx, char *path)
// {
// 	t_image	img;

// 	img.pointer = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
// 	img.pixels  = mlx_get_data_addr(img.reference, &img.bits_per_pixel, &img.line_size, &img.endian);
// 	return (img);
// }

int	close(int keycode, t_vars *vars)
{
	mlx_destroy_window(vars->mlx, vars->win);
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
	void	*mlx;
	void	*mlx_win;
	t_vars	vars;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	my_mlx_pixel_put(&img, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(vars.win, 2, 1L << 0, close, &vars);
	mlx_loop(mlx);
}
