#include "push_swap.h"

void	push(t_list **target, t_list **source)
{
	t_list	*temp;

	if (*source == NULL)
		return ;
	temp = (*source);
	(*source) = temp->next;
	temp->next = *target;
	*target = temp;
}

void	pa(t_push_swap	*info)
{
    write(1, "pa\n", 3);
    push(info->stack_a, info->stack_b);
    info->length_a++;
    info->length_b--;
    info->max_a = find_max(info->stack_a);
    info->min_a = find_min(info->stack_a);
    info->max_b = find_max(info->stack_b);
    info->min_b = find_min(info->stack_b);
}

void	pb(t_push_swap	*info)
{
    write(1, "pa\n", 3);
    push(info->stack_b, info->stack_a);
    info->length_a--;
    info->length_b++;
    info->max_a = find_max(info->stack_a);
    info->min_a = find_min(info->stack_a);
    info->max_b = find_max(info->stack_b);
    info->min_b = find_min(info->stack_b);
}