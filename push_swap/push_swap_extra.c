/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:00:16 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/24 20:00:20 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int	min(int a, int b, int c, int d)
{
	if (d < a && d < b && d < c)
		return (d);
	if (c < a && c < b && c < d)
		return (c);
	if (b < a && b < c && b < d)
		return (b);
	return (a);
}

int	find_length(t_list **head)
{
	int		length;
	t_list	*curr;

	if (!head || !*head)
		return (0);
	length = 1;
	curr = *head;
	while (curr->next)
	{
		curr = curr->next;
		length++;
	}
	return (length);
}
