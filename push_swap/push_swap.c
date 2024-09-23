#include "push_swap.h"

void	set_up(t_push_swap	*info)
{
	info->length_a = find_length(info->stack_a);
	info->length_b = 1;
}

int	main(int argc, char **argv)
{
	t_push_swap	info;

	info.stack_a = init_stack(argc, argv);
	info.stack_b = (t_list **)malloc(sizeof(t_list *));
	if (!info.stack_b)
		terminate(info.stack_a, info.stack_b);
	*info.stack_b = NULL;
	if (find_length(info.stack_a) < 2 || check_duplicates(info.stack_a))
		terminate(info.stack_a, info.stack_b);
	write(1, "pb\n", 3);
    push(info.stack_b, info.stack_a);
	set_up(&info);
	
	while (info.length_a > 3)
		make_move(&info);
	if (find_length(info.stack_a) == 3)
		solve_three(&info);
	else if (find_length(info.stack_a) == 2)
		solve_two(&info);
	while (info.length_b)
		push_back(&info);
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

void	solve_three(t_list **stack_a)
{

}

void	solve_two(t_list **stack_a)
{

}

void	push_back(t_push_swap	*info)
{

}
