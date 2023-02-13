/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:49 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/13 15:31:42 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>

// typedef struct s_data {
// 	void	*img;
// 	char	*addr;
// 	int		bits_per_pixel;
// 	int		line_length;
// 	int		endian;
// }				t_data;

typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

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
	int			colcoins;
	int			needcoins;
	int			structlen;
}				t_mega;

//other tut:



typedef struct s_color {
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

// t_window	ft_new_window(void *mlx, int widht, int height, char *name);
// t_image		ft_new_sprite(void *mlx, char *path);

// t_color		new_color(int r, int g, int b, int a);
// void		turn_img_to_color(t_image *image, t_color color);

// int			ft_input(int key, void *program);
// int			ft_update (void *param);

//# define WINDOW_WIDTH 1200
//# define WINDOW_HEIGHT 600

#endif
