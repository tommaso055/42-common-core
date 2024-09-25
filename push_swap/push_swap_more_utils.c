/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_more_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:00:41 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/24 20:00:43 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	solve_two(t_push_swap *info)
{
	if ((*(info->stack_a))->content > (*(info->stack_a))->next->content)
		ra(info);
	info->higher = (*(info->stack_a))->next->content;
	info->lower = (*(info->stack_a))->content;
}

void	push_back(t_push_swap *info)
{
	while (info->length_b)
	{
		if (info->rotations == 0)
		{
			if ((*(info->stack_b))->content < info->higher)
			{
				rra(info);
				info->rotations++;
			}
		}
		if (info->rotations == 1)
		{
			if ((*(info->stack_b))->content < info->lower)
			{
				rra(info);
				info->rotations++;
			}
		}
		pa(info);
	}
	while (info->rotations++ < 2)
		rra(info);
}

int	count_moves(t_push_swap	*info, int position, int content)
{
	int	ra;
	int	rra;
	int	rb;
	int	rrb;
	int	moves;

	ra = position;
	rb = find_target_position(info->stack_b, content);
	rra = info->length_a - position;
	rrb = info->length_b - rb;
	moves = min(max(ra, rb), max(rra, rrb), ra + rrb, rb + rra);
	return (moves);
}

int	find_target_position(t_list **stack_b, int a_c)
{
	t_list	*curr;
	int		position;
	int		t_position;
	int		t_c;

	position = 1;
	t_position = 0;
	t_c = (*stack_b)->content;
	curr = (*stack_b)->next;
	while (curr)
	{
		if (t_c > a_c && (curr->content > t_c || curr->content < a_c))
		{
			t_position = position;
			t_c = curr->content;
		}
		else if (t_c < a_c && curr->content < a_c && curr->content > t_c)
		{
			t_position = position;
			t_c = curr->content;
		}
		curr = curr->next;
		position++;
	}
	return (t_position);
}

void	put_str(char *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		write (1, &s[i++], 1);
}
