/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 10:56:49 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/15 10:51:24 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include <stdlib.h>
# include "mlx/mlx.h"
# include "libft/libft.h"
# include <fcntl.h>

# ifndef IMS
#  define IMS 128
# endif
// big = 128 small = 24 Do not use this as a macro, make a variable in mapcheck
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
	int			collected;
	int			colcoins;
	int			needcoins;
	int			structlen;
	int			stepsdone;
}				t_mega;

#endif
