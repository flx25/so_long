/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:49 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/23 18:11:31 by fvon-nag         ###   ########.fr       */
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

#endif
