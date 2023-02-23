/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:49 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/23 18:42:17 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct s_matrix {
	char	c;
	bool	v;
}				t_matrix;

typedef struct s_vecchar
{
	int		x;
	int		y;
	char	c;
}				t_vecchar;

typedef struct s_image {
	void		*reference;
	t_vector	size;
	char		*pixels;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
}				t_image;

typedef struct s_window {
	void		*reference;
	t_vector	size;
}				t_window;

typedef struct s_program {
	void		*mlx;
	t_window	window;
	t_image		sprite;
	t_vector	sprite_position;
}				t_program;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct s_mega {
	t_vars		s_vars;
	void		*img;
	char		*addr;
	t_image		s_image;
	t_vector	size;
	int			x;
	int			y;
	int			px;
	int			py;
	char		type;
	int			collected;
	int			colcoins;
	int			needcoins;
	int			structlen;
	int			stepsdone;
	int			is;
	int			*msize;
}				t_mega;

t_mega		*initmap(char *argv1);
char		*readmap(char *map);
int			checks(char *argv1);
int			checkformat(char *argv1);
int			mapcheck(char *argv1);
int			checkrect(char *argv1);
int			pathcheck(char *argv1);
t_matrix	**allocmapsize(char *map);
int			*mapsize(char *map);
void		mapdrawch(char *map, t_matrix **mapgr);
int			checkchars(char *map);
int			checkmin(char *map);
int			checkpath(t_matrix **mapgr, int xsize, int ysize);
int			*givep(t_matrix **mapgr, int xsize);
void		dfs(t_matrix **mapgr, int x, int y);
void		usemap(char *arg1, t_mega *mega);
void		mapdraw(char *map, t_mega *mega);
void		drawit2(char c, t_vector xy, t_mega *mega, int *i);
void		drawit1(char c, t_vector xy, t_mega *mega, int *i);
void		drawitpre(char c, int x, int y, t_mega *mega);


#endif
