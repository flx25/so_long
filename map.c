/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 17:55:50 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/23 18:06:37 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	mapcheck(char *argv1)
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

int	checkformat(char *argv1)
{
	int	len;
	int	out;

	len = ft_strlen(argv1);
	out = ft_strncmp(argv1 + len - 4, ".ber", 4);
	if (out != 0)
		ft_printf("Error\nMap needs to be in .ber format!\n");
	return (out);
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
		free(temp);
	}
	close(fd);
	return (out);
}
