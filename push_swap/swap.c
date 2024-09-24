#include "push_swap.h"

void	swap(t_list **head)
{
	t_list	*temp;

	if (*head == NULL || (*head)->next == NULL)
		return ;
	temp = (*head)->next;
	(*head)->next = temp->next;
	temp->next = (*head);
	*head = temp;
}

void	sa(t_push_swap	*info)
{
	write(1, "sa\n", 3);
	swap(info->stack_a);
}

void	sb(t_push_swap	*info)
{
	write(1, "sb\n", 3);
	swap(info->stack_b);
}

void	ss(t_push_swap	*info)
{
	write(1, "ss\n", 3);
	swap(info->stack_a);
	swap(info->stack_b);
}
