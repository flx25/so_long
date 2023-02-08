/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/08 15:28:03 by fvon-nag         ###   ########.fr       */
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

int	main(void)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		widh = 15;
	int		height = 7;
	void	*cat;


	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"My first window!");
	cat = mlx_xpm_file_to_image(mlx_ptr, "cat.xpm", &widh, &height);
	mlx_put_image_to_window(mlx_ptr, win_ptr, cat, 0, 0);
	mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	//mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
}
