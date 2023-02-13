/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/13 11:38:06 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// CHECK FOR LEAKS
// debugging flags on
// may other flags off

void	ft_new_sprite(t_mega *mega, char *path)
{
	mega->pointer = mlx_xpm_file_to_image(mega->mlx, path, &mega->size.x,
			&mega->size.y);
	mega->pixels = mlx_get_data_addr(mega->pointer, &mega->bits_per_pixel,
			&mega->line_size, &mega->endian);
}

// void move(int x, int y, t_vars *vars, t_image *img)
// {
// 	mlx_put_image_to_window(vars->mlx, vars->win, img[2].pointer,
// 		g_player.x, g_player.y);
// 	mlx_put_image_to_window(vars->mlx, vars->win, img[2].pointer,
// 		g_player.x + x, g_player.y + y);

// 	g_player.x += x;
// 	g_player.y += y;

// }
// int	key(int keycode, t_vars *vars, t_image *img)
// {
// 	if (keycode == 13)
// 		move(0, 128, vars, img);
// 	if (keycode == 1)
// 		ft_printf("DOWN (S)\n");
// 	if (keycode == 0)
// 		ft_printf("LEFT (A)\n");
// 	if (keycode == 2)
// 		ft_printf("RIGHT (D)\n");
// 	if (keycode == 53)
// 	{
// 		mlx_destroy_window(vars->mlx, vars->win);
// 		exit(0);
// 	}
// 	// maybe need more to close
// 	return (0);
// }

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

void	mapcheck(char *map)
{

}

void	drawit(char c, int x, int y, t_mega *mega)
{
	if (c == '1')
		mlx_put_image_to_window(mega[0].mlx, mega[0].win, mega[0].pointer,
			x * 128, y * 128);
	if (c == '0')
		mlx_put_image_to_window(mega[0].mlx, mega[0].win, mega[1].pointer,
			x * 128, y * 128);
	if (c == 'E')
	{
		mlx_put_image_to_window(mega[0].mlx, mega[0].win, mega[2].pointer,
			x * 128, y * 128);
		//add positions to mega struct
	}


}

void mapdraw(char *map, t_mega **mega)
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

void	usemap(char *arg1, t_mega **mega)
{
	char	*map;

	ft_printf("%s \n", map = readmap(arg1));
	//mapcheck(map);
	mapdraw(map, mega);

}

void	*initimages(t_mega **mega)
{
	ft_new_sprite(mega[0], "Bricks_11-128x128.xpm");
	ft_new_sprite(mega[1], "Tile_14-128x128.xpm");
	ft_new_sprite(mega[2], "Ghost.xpm");


}

int ft_strlen_nnl(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] != '\n')
			count++;
		i++;
	}
	return (count);
}

t_mega **initmap(char *argv1, t_mega **mega)
{
	char	*map;
	int		msize;
	int		i;
	t_mega	**out;

	map = readmap(argv1);
	msize = ft_strlen_nnl(map);
	i = 0;

	out = (t_mega **) ft_calloc(msize + 1, sizeof(t_mega *));

	while (i <= msize)
	{
		out[i] = (t_mega *) ft_calloc(1, sizeof(t_mega));
		i++;
	}
	out[0]->structlen = msize;
	free(map);
	return (out);
}

int	main(int argc, char **argv)
{
	t_mega	**mega;

	if (argc != 2)
		return (ft_printf("Please give a map as an argument!\n"));
	mega = initmap(argv[1], mega);
	mega[0]->mlx = mlx_init();
	mega[0]->win = mlx_new_window(mega[0]->mlx, 2400, 1200, "so_long");
	initimages(mega);
	// mlx_key_hook(mega[0].win, key, &mega);
	usemap(argv[1], mega);
	mlx_hook(mega[0]->win, 17, 0, ft_close, &mega);
	mlx_loop(mega[0]->mlx);
}
