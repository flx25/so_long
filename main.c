/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:32 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/23 08:37:49 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

// CHECK FOR LEAKS
// debugging flags on
// may other flags off
// do not forget to print the map errors

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

void	destroyimages(t_mega *mega)
{

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
		destroyimages(mega);
		mlx_destroy_window(mega[0].s_vars.mlx, mega[0].s_vars.win);
		mlx_destroy_display(mega[0].s_vars.mlx, mega[0].s_vars.win);
		free(mega);
		exit(0);
			// maybe need more to close
	}
	return (0);
}

int	ft_close(void)
{
	exit(0);
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
	close(fd);
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

t_matrix	**allocmapsize(char *map)
{
	t_matrix	**mapgr;
	t_matrix	*data;
	int			*msize;
	int			i;

	msize = mapsize(map);
	data = ft_calloc(msize[0] * msize[1], sizeof(t_matrix));
	mapgr = ft_calloc(msize[0], sizeof(t_matrix *));
	i = 0;
	while (i < msize[0])
	{
		mapgr[i] = data + i * msize[1];
		i++;
	}
	free(msize);
	return (mapgr);
}
void mapdrawch(char *map, t_matrix **mapgr)
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
		{
			mapgr[x][y].c = map[i];
			x++;
		}
		i++;
	}
}

void	DFS(t_matrix **mapgr, int x, int y)
{
	mapgr[x][y].v = true;
	if (mapgr[x + 1][y].c != '1' && mapgr[x + 1][y].v != 1)
		DFS(mapgr, x + 1, y);
	if (mapgr[x][y + 1].c != '1' && mapgr[x][y + 1].v != 1)
		DFS(mapgr, x, y + 1);
	if (mapgr[x - 1][y].c != '1' && mapgr[x - 1][y].v != 1)
		DFS(mapgr, x - 1, y);
	if (mapgr[x][y - 1].c != '1' && mapgr[x][y - 1].v != 1)
		DFS(mapgr, x, y - 1);
}

int	*givep(t_matrix **mapgr, int xsize)
{
	int	x;
	int	y;
	int	*out;

	out = ft_calloc(3, sizeof(int));
	x = 0;
	y = 0;
	while (mapgr[x][y].c != '\0')
	{
		while (x < xsize)
		{
			if (mapgr[x][y].c == 'P')
			{
				out[0] = x;
				out[1] = y;
				return (out);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (NULL);
}

int	checkpath(t_matrix **mapgr, int xsize)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (mapgr[x][y].c != '\0')
	{
		while (x < xsize)
		{
			if ((mapgr[x][y].c == 'P' || mapgr[x][y].c == 'E'
				|| mapgr[x][y].c == 'C') && mapgr[x][y].v == 0)
			{
				ft_printf("Error\nNo valid path on the map!\n");
				return (1);
			}
			x++;
		}
		y++;
		x = 0;
	}
	return (0);
}

int checkmin(char *map)
{
	int	i;
	int	p;
	int	c;
	int	e;

	e = 0;
	i = 0;
	p = 0;
	c = 0;
	while (map[i] != '\0')
	{
		if (map[i] == 'P')
			p++;
		if (map[i] == 'E')
			e++;
		if (map[i] == 'C')
			c++;
	i++;
	}
	if (p != 1 || c < 1 || e != 1)
		return (ft_printf("Error\nMap needs 1 E, 1 P and at least 1 C!\n"), 1);
	else
		return (0);
}

int	checkchars(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\0')
	{
		if (map[i] != '\n' || map[i] != '1' || map[i] != '0'
			|| map[i] != 'P' || map[i] != 'E' || map[i] != 'C')
		{
			ft_printf("Error\nForbidden characters!");
			return (1);
		}
		i++;
	}
	return (0);
}

int	mapcheck (char *argv1)
{
	char		*map;
	int			error;

	error = 0;
	map = readmap(argv1);
	error += checkchars(map);
	error += checkmin(map);
	free(map);
	return (error);
}

int	pathcheck(char *argv1)
{
	char		*map;
	t_matrix	**mapgr;
	int			*player;
	int			error;
	int			*mapsizei;

	error = 0;
	map = readmap(argv1);
	mapgr = allocmapsize(map);
	mapdrawch(map, mapgr);
	mapsizei = mapsize(map);
	player = givep(mapgr, mapsizei[0]);
	DFS(mapgr, player[0], player[1]);
	error = checkpath(mapgr, mapsizei[0]);
	free(player);
	free(mapsizei);
	free(mapgr[0]);
	free(mapgr);
	free(map);
	return (error);
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
		{
			drawit(map[i], x, y, mega);
			x++;
		}
	i++;
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
			"small/winning_s.xpm");
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
	t_mega	*out;

	map = readmap(argv1);
	msize = ft_strlen_nnl(map);

	out = (t_mega *) ft_calloc(msize + 1, sizeof(t_mega));
	out[0].structlen = msize;
	free(map);
	return (out);
}

void	initwindow(t_mega **mega, char *argv1)
{
	char	*map;
	int		*msize;

	map = readmap(argv1);
	msize = mapsize(map);
	(*mega)[0].msize = msize; //remember to free
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

int	checkformat (char *argv1)
{
	int	len;
	int	out;

	len = ft_strlen(argv1);
	out = ft_strncmp(argv1 + len - 4, ".ber", 4);
	if (out != 0)
		ft_printf("Error\nMap needs to be in .ber format!\n");
	return (out);
}

int rectch2(t_matrix **mapgr, int xmax, int ymax)
{
	int	i;

	i = 0;
	while (i < xmax)
	{
		if (mapgr[i][ymax - 1].c != '1')
			return (1);
	i++;
	}
	i = 0;
	while (i < ymax)
	{
		if (mapgr[xmax - 1][i].c != '1')
			return (1);
		i++;
	}
	i = 0;
	return (0);
}

int rectch1(t_matrix **mapgr, int xmax, int ymax)
{
	int	i;

	i = 0;
	while (i < xmax)
	{
		if (mapgr[i][0].c != '1')
			return (1);
	i++;
	}
	i = 0;
	while (i < ymax)
	{
		if (mapgr[0][i].c != '1')
			return (1);
		i++;
	}
	i = 0;
	if (rectch2(mapgr, xmax, ymax) == 1)
		return (1);
	return (0);
}

int	checkrect(char *argv1)
{
	char		*map;
	t_matrix	**mapgr;
	int			error;
	int			*mapsizei;

	error = 0;
	map = readmap(argv1);
	mapgr = allocmapsize(map);
	mapdrawch(map, mapgr);
	mapsizei = mapsize(map);
	error = rectch1(mapgr, mapsizei[0], mapsizei[1]);
	free(map);
	free(mapgr[0]);
	free(mapgr);
	free(mapsizei);
	if (error != 0)
		ft_printf("Error\nMap needs to be rectangular, surrounded by walls!\n");
	return (error);
}


int	checks(char *argv1)
{
	if (checkformat(argv1) != 0)
		return (1);
	if (mapcheck(argv1) != 0)
		return (1);
	if (checkrect(argv1) != 0)
		return (1);
	if (pathcheck(argv1) != 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_mega	*mega;

	if (argc != 2)
		return (ft_printf("Error\nPlease give a map as an argument!\n"));
	if (checks(argv[1]) != 0)
		exit(0); // maybe need to free more
	mega = initmap(argv[1]);
	initwindow(&mega, argv[1]);
	mlx_key_hook(mega[0].s_vars.win, key, mega);
	usemap(argv[1], mega);
	mlx_hook(mega[0].s_vars.win, 17, 0, ft_close, mega);
	mlx_loop(mega[0].s_vars.mlx);
	mlx_destroy_window(mega[0].s_vars.mlx, mega[0].s_vars.win);
	mlx_destroy_display(mega[0].s_vars.mlx, mega[0].s_vars.win);
	//destroy images
	// get library with destroy images
	//use leaks
	// leaks --atExit -- ./so_long ...
}
