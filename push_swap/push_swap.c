#include "push_swap.h"

void	set_up(t_push_swap	*info)
{
	info->length_a = find_length(info->stack_a);
	info->length_b = 1;
	info->max_a = find_max(info->stack_a);
	info->min_a = find_min(info->stack_a);
	info->max_b = (*(info->stack_b))->content;
	info->min_b = (*(info->stack_b))->content;
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
	write(1, "pa\n", 3);
    push(info.stack_a, info.stack_b);
	set_up(&info);
	
	// algorithm here -> ...
}

int	check_duplicates(t_list **head)
{

}

void	find_move(t_list **stack_a, t_list **stack_b)
{

}