/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:32:15 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/24 09:34:55 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	destroyimages(t_mega *mega)
{
	ft_printf("image 0 %i", mlx_destroy_image(mega[0].s_vars.mlx, mega[0].s_image.reference));
	ft_printf("image 1 %i", mlx_destroy_image(mega[0].s_vars.mlx, mega[1].s_image.reference));
	mlx_destroy_image(mega[0].s_vars.mlx, mega[2].s_image.reference);
	mlx_destroy_image(mega[0].s_vars.mlx, mega[3].s_image.reference);
	mlx_destroy_image(mega[0].s_vars.mlx, mega[4].s_image.reference);
	mlx_destroy_image(mega[0].s_vars.mlx, mega[5].s_image.reference);
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
}

t_image	ft_new_sprite(void *mlx, char *path)
{
	t_image	img;

	img.reference = mlx_xpm_file_to_image(mlx, path, &img.size.x, &img.size.y);
	img.pixels = mlx_get_data_addr(img.reference, &img.bits_per_pixel,
			&img.line_size, &img.endian);
	return (img);
}
