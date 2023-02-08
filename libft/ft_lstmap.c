/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fvon-nag <fvon-nag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:57:55 by fvon-nag          #+#    #+#             */
/*   Updated: 2022/12/21 15:01:20 by fvon-nag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

static t_list	*loop(t_list *current, t_list *outfirst, void *(*f)(void *),
					void(*del)(void *))
{
	t_list	*outnew;

	while (current != NULL)
	{
		outnew = ft_lstnew(f(current->content));
		if (outnew == NULL)
		{
			del(outnew->content);
			del(outnew);
			return (NULL);
		}
		ft_lstadd_back(&outfirst, outnew);
		if (current->next != NULL)
			current = current->next;
		else
		{
			return (outfirst);
		}
	}
	return (outfirst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
			void (*del)(void *))
{
	t_list	*current;
	t_list	*outfirst;

	if (lst == NULL || f == NULL || del == NULL)
		return (NULL);
	current = lst;
	outfirst = ft_lstnew(f(current->content));
	if (current->next != NULL)
		current = current->next;
	return (loop(current, outfirst, f, del));
}
