/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:56:31 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/02/08 09:58:45 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char	*readtostr(int fd, char *str)
{
	char	*buff;
	int		readstat;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	readstat = 1;
	while (!ft_gnl_strchr(str, '\n') && readstat != 0)
	{
		readstat = read(fd, buff, BUFFER_SIZE);
		if (readstat == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		buff[readstat] = '\0';
		str = ft_gnl_strjoin(str, buff);
	}
	free(buff);
	return (str);
}

char	*ft_getline(char *str)
{
	int		i;
	char	*nstr;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	nstr = malloc((i + 2) * sizeof(char));
	if (!nstr)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		nstr[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		nstr[i] = str[i];
		i++;
	}
	nstr[i] = '\0';
	return (nstr);
}

char	*getnewstr(char *str)
{
	int		i;
	int		j;
	char	*nstr;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	nstr = malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!nstr)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		nstr[j++] = str[i++];
	nstr[j] = '\0';
	free(str);
	if (nstr[0] == '\0')
		return (free(nstr), NULL);
	return (nstr);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = readtostr(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = ft_getline(str[fd]);
	str[fd] = getnewstr(str[fd]);
	return (line);
}
