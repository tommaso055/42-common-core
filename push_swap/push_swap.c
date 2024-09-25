/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:01:07 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/24 20:01:10 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	set_up(t_push_swap *info)
{
	info->length_a = find_length(info->stack_a);
	info->length_b = 0;
	info->rotations = 0;
}

int	main(int argc, char **argv)
{
	t_push_swap	info;
	char		**split;
	int			i;

	i = 0;
	if (argc == 1)
		return (0);
	if (argc == 2)
	{
		split = ft_split(argv[1], ' ');
		info.stack_a = init_stack(ft_matrixlen(split), argv, 0);
		while(split[i])
			free(split[i++]);
		free(split);
	}
	else
		info.stack_a = init_stack(argc, argv, 1);
	info.stack_b = (t_list **)malloc(sizeof(t_list *));
	set_up(&info);
	if (info.length_a == 2)
	{
		solve_two(&info);
		terminate(info.stack_a, info.stack_b, NULL);
	}
	pb(&info);
	while (info.length_a > 2)
		make_move(&info);
	solve_two(&info);
	order_b(&info);
	push_back(&info);
	terminate(info.stack_a, info.stack_b, NULL);
}

int	check_duplicates(t_list **stack_a)
{
	t_list	*curr;
	t_list	*temp_curr;

	curr = (*stack_a);
	while (curr)
	{
		temp_curr = curr->next;
		while (temp_curr)
		{
			if (curr->content == temp_curr->content)
				return (1);
			temp_curr = temp_curr->next;
		}
		curr = curr->next;
	}
	return (0);
}

void	set_vars_order_b(t_moves *moves)
{
	moves->rrb = 0;
	moves->ra = 0;
	moves->rra = 0;
	moves->rb = 0;
	moves->position = 1;
	moves->best_position = 0;
}

void	order_b(t_push_swap *info)
{
	t_list	*curr;
	t_moves	vars;

	set_vars_order_b(&vars);
	vars.best_content = (*(info->stack_b))->content;
	curr = (*(info->stack_b))->next;
	while (curr)
	{
		if (curr->content > vars.best_content)
		{
			vars.best_content = curr->content;
			vars.best_position = vars.position;
		}
		curr = curr->next;
		vars.position++;
	}
	if (vars.best_position < info->length_b - vars.best_position)
		vars.rb = vars.best_position;
	else
		vars.rrb = info->length_b - vars.best_position;
	arrange(info, &vars);
}
