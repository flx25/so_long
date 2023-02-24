/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/24 09:59:51 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_close(t_mega *mega)
{
	destroyimages(mega);
	mlx_destroy_window(mega[0].s_vars.mlx, mega[0].s_vars.win);
	free(mega);
	exit(0);
	return (0);
}

int	key(int keycode, t_mega *mega)
{
	if (keycode == 13)
		premove(0, -mega[0].is, mega);
	if (keycode == 1)
		premove(0, mega[0].is, mega);
	if (keycode == 0)
		premove(-mega[0].is, 0, mega);
	if (keycode == 2)
		premove(mega[0].is, 0, mega);
	if (keycode == 53)
	{
		destroyimages(mega);
		mlx_destroy_window(mega[0].s_vars.mlx, mega[0].s_vars.win);
		free(mega);
		exit(0);
	}
	return (0);
}

void	initwindow(t_mega **mega, char *argv1)
{
	char	*map;
	int		*msize;

	map = readmap(argv1);
	msize = mapsize(map);
	(*mega)[0].msize = msize;
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

int	main(int argc, char **argv)
{
	t_mega	*mega;

	if (argc != 2)
		return (ft_printf("Error\nPlease give a map as an argument!\n"));
	if (checks(argv[1]) != 0)
		exit(0);
	mega = initmap(argv[1]);
	initwindow(&mega, argv[1]);
	mlx_key_hook(mega[0].s_vars.win, key, mega);
	usemap(argv[1], mega);
	mlx_hook(mega[0].s_vars.win, 17, 0, ft_close, mega);
	mlx_loop(mega[0].s_vars.mlx);
}
