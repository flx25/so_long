/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 08:36:09 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/24 09:30:15 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

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

void	premove(int x, int y, t_mega *mega)
{
	int	tcret;

	tcret = tilecheck(mega[0].px + x, mega[0].py + y, mega);
	if (tcret == -1)
		move1(x, y, mega);
	else if (mega[tcret].type == 'C' )
		move2(x, y, mega, tcret);
	else if (mega[tcret].type == 'E' && mega[0].colcoins == mega[0].needcoins)
		move3(x, y, mega);
	ft_printf("steps done: %i\n", mega[0].stepsdone);
}

void	move1(int x, int y, t_mega *mega)
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

void	move2(int x, int y, t_mega *mega, int tcret)
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

void	move3(int x, int y, t_mega *mega)
{
	mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
		mega[3].s_image.reference, mega[0].px, mega[0].py);
	mlx_put_image_to_window(mega[0].s_vars.mlx, mega[0].s_vars.win,
		mega[1].s_image.reference, mega[0].px, mega[0].py);
	mega[0].px = mega[0].px + x;
	mega[0].py = mega[0].py + y;
	mega[0].stepsdone += 1;
	ft_close(mega);
}
