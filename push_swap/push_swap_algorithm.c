/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_algorithm.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:58:42 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/24 19:58:51 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	make_move(t_push_swap	*info)
{
	t_list		*curr;
	t_make_move	vars;

	set_make_move(info, &vars, &curr);
	curr = curr->next;
	while (curr)
	{
		vars.moves = count_moves(info, vars.position, curr->content);
		if (vars.moves < vars.least_moves)
		{
			vars.least_moves = vars.moves;
			vars.best_content = curr->content;
			vars.best_position = vars.position;
		}
		vars.position++;
		curr = curr->next;
	}
	vars.t_position = find_target_position(info->stack_b, vars.best_content);
	push_to_b(info, vars.best_position, vars.t_position);
}

void	set_zero(int *a, int *b)
{
	*a = 0;
	*b = 0;
}

void	push_to_b(t_push_swap *info, int source_position, int target_position)
{
	t_moves	m;
	int		min_m;

	m.ra = source_position;
	m.rb = target_position;
	m.rra = info->length_a - m.ra;
	m.rrb = info->length_b - m.rb;
	min_m = min(max(m.ra, m.rb), max(m.rra, m.rrb), m.ra + m.rrb, m.rb + m.rra);
	if (max(m.ra, m.rb) <= min_m)
		set_zero(&m.rra, &m.rrb);
	else if (max(m.rra, m.rrb) <= min_m)
		set_zero(&m.ra, &m.rb);
	else if (m.ra + m.rrb <= min_m)
		set_zero(&m.rra, &m.rb);
	else if (m.rb + m.rra <= min_m)
		set_zero(&m.ra, &m.rrb);
	arrange(info, &m);
	pb(info);
}

void	arrange(t_push_swap *info, t_moves *moves)
{
	while (moves->ra > 0 && moves->rb > 0)
	{
		moves->ra--;
		moves->rb--;
		rr(info);
	}
	while (moves->rra > 0 && moves->rrb > 0)
	{
		moves->rra--;
		moves->rrb--;
		rrr(info);
	}
	while ((moves->ra)-- > 0)
		ra(info);
	while ((moves->rb)-- > 0)
		rb(info);
	while ((moves->rra)-- > 0)
		rra(info);
	while ((moves->rrb)-- > 0)
		rrb(info);
}

void	set_make_move(t_push_swap *info, t_make_move *vars, t_list **curr)
{
	*curr = *(info->stack_a);
	vars->position = 1;
	vars->least_moves = count_moves(info, 0, (*curr)->content);
	vars->best_content = (*curr)->content;
	vars->best_position = 0;
}