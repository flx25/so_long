/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:49 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/09 14:08:27 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include <stdlib.h>
# include "mlx/mlx.h"
# include "libft/libft.h"

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

//other tut:
typedef struct s_vector
{
	int	x;
	int	y;
}				t_vector;

typedef struct s_image
{
	void		*pointer;
	t_vector	size;
	char		*pixels;
	int			bits_per_pixel;
	int			line_size;
	int			endian;
}	t_image;

typedef struct s_window {
	void		*reference;
	t_vector	size;
}				t_window;

typedef struct s_color {
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

typedef struct s_program {
	void		*mlx;
	t_window	window;
	t_image		sprite;
	t_vector	sprite_position;
}				t_program;

// t_window	ft_new_window(void *mlx, int widht, int height, char *name);
// t_image		ft_new_sprite(void *mlx, char *path);

// t_color		new_color(int r, int g, int b, int a);
// void		turn_img_to_color(t_image *image, t_color color);

// int			ft_input(int key, void *program);
// int			ft_update (void *param);

//# define WINDOW_WIDTH 1200
//# define WINDOW_HEIGHT 600

#endif
