/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:02:54 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/24 20:02:55 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_list **head)
{
	t_list	*tail;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	tail = *head;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = *head;
	*head = (*head)->next;
	tail->next->next = NULL;
	return ;
}

void	ra(t_push_swap	*info)
{
	write(1, "ra\n", 3);
	rotate(info->stack_a);
}

void	rb(t_push_swap	*info)
{
	write(1, "rb\n", 3);
	rotate(info->stack_b);
}

void	rr(t_push_swap	*info)
{
	write(1, "rr\n", 3);
	rotate(info->stack_a);
	rotate(info->stack_b);
}
