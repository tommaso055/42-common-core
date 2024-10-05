/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correction.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 21:17:17 by tdonato           #+#    #+#             */
/*   Updated: 2024/10/05 21:17:19 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	in_order(t_list **stack_a)
{
	t_list	*curr;
	int		prev;

	curr = *stack_a;
	prev = curr->content;
	curr = curr->next;
	while (curr)
	{
		if (curr->content <= prev)
			return (0);
		prev = curr->content;
        curr = curr->next;
	}
	return (1);
}

void	solve_three(t_push_swap *info)
{
	int	a;
	int	b;
	int	c;

	a = (*(info->stack_a))->content;
	b = (*(info->stack_a))->next->content;
	c = (*(info->stack_a))->next->next->content;
	if (a < b && b < c)
		situation(1, info);
	if (a < c && c < b)
		situation(2, info);
	if (b < a && a < c)
		situation(3, info);
	if (b < c && c < a)
		situation(4, info);
	if (c < a && a < b)
		situation(5, info);
	if (c < b && b < a)
		situation(6, info);
	terminate(info->stack_a, info->stack_b, NULL);
}

void	situation(int situation, t_push_swap *info)
{
	if (situation == 2)
	{
		rra(info);
		sa(info);
	}
	if (situation == 3)
		sa(info);
	if (situation == 4)
		rra(info);
	if (situation == 5)
		ra(info);
	if (situation == 6)
	{
		sa(info);
		rra(info);
	}
}
