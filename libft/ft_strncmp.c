/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 13:15:37 by fvon-nag          #+#    #+#             */
/*   Updated: 2023/01/05 11:31:30 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while ((size_t)i < n - 1 && s1[i] != '\0' && s2[i] != '\0'
		&& s1[i] == s2[i])
	{
	i++;
	}
	return ((unsigned char) s1[i] - (unsigned char) s2[i]);
}
