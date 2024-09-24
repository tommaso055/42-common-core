/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:03:09 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/24 20:03:10 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	reverse_rotate(t_list **head)
{
	t_list	*new_tail;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	new_tail = *head;
	while (new_tail->next->next != NULL)
		new_tail = new_tail->next;
	new_tail->next->next = *head;
	*head = new_tail->next;
	new_tail->next = NULL;
}

void	rra(t_push_swap	*info)
{
	write(1, "rra\n", 4);
	reverse_rotate(info->stack_a);
}

void	rrb(t_push_swap	*info)
{
	write(1, "rrb\n", 4);
	reverse_rotate(info->stack_b);
}

void	rrr(t_push_swap	*info)
{
	write(1, "rrr\n", 4);
	reverse_rotate(info->stack_a);
	reverse_rotate(info->stack_b);
}
