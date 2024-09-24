#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_push_swap	info;

	if (argc == 1)
		return (0);
	info.stack_a = init_stack(argc, argv);
	info.stack_b = (t_list **)malloc(sizeof(t_list *));
	if (!info.stack_b)
		terminate(info.stack_a, info.stack_b);
	*info.stack_b = NULL;
	if (find_length(info.stack_a) < 2 || check_duplicates(info.stack_a))
		terminate(info.stack_a, info.stack_b);
	info.length_a = find_length(info.stack_a);
	info.length_b = 0;
	info.rotations = 0;
	if (info.length_a == 2)
	{
		solve_two(&info);
		terminate(info.stack_a, info.stack_b);
	}
	pb(&info);
	while (info.length_a > 2)
		make_move(&info);
	solve_two(&info);
	order_b(&info);
	while (info.length_b)
		push_back(&info);
	while (info.rotations++ < 2)
		rra(&info);
	terminate(info.stack_a, info.stack_b);
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

void	order_b(t_push_swap *info)
{
	int		best_position;
	int		best_content;
	int		position;
	t_list	*curr;
	t_moves	moves;

	position = 1;
	best_position = 0;
	best_content = (*(info->stack_b))->content;
	curr = (*(info->stack_b))->next;
	while (curr)
	{
		if (curr->content > best_content)
		{
			best_content = curr->content;
			best_position = position;
		}
		curr = curr->next;
		position++;
	}
	moves.rrb = 0;
	moves.ra = 0;
	moves.rra = 0;
	moves.rb = 0;
	if (best_position < info->length_b - best_position)
		moves.rb = best_position;
	else
		moves.rrb = info->length_b - best_position;
	arrange(info, &moves);
}

void	solve_two(t_push_swap *info)
{
	if ((*(info->stack_a))->content > (*(info->stack_a))->next->content)
		ra(info);
	info->higher = (*(info->stack_a))->next->content;
	info->lower = (*(info->stack_a))->content;
}

void	push_back(t_push_swap *info)
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
