/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 21:42:45 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/16 21:42:47 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*return_values;
	t_list	*curr;
	void	*data;

	return_values = NULL;
	curr = NULL;
	while (lst != NULL)
	{
		data = f(lst->content);
		if (data == NULL)
		{
			ft_lstclear(&return_values, del);
			return (NULL);
		}
		curr = ft_lstnew(data);
		if (curr == NULL)
		{
			ft_lstclear(&return_values, del);
			return (NULL);
		}
		ft_lstadd_back(&return_values, curr);
		lst = lst->next;
	}
	return (return_values);
}
