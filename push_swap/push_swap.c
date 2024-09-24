#include "push_swap.h"

int	main()
{
	t_push_swap	info;

	int argc = 10;
	char *argv[10] = {"push_swap", "5", "2", "7", "1", "6", "3", "9", "4", "8"};

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
	while (info.length_b)
		push_back(&info);
	while (info.rotations < 2)
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