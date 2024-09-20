#include "push_swap.h"

void print_list(t_list *head)
{
    t_list *current = head;

    if (current == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    while (current)
    {
        printf("%d", current->content);
        if (current->next)
            printf(" -> ");
        current = current->next;
    }
    printf(" -> NULL\n");
}

int main(int argc, char **argv)
{
	t_push_swap	info;

    if (argc < 2)
	{
		printf("Usage: ./a.out [numbers...]\n");
		return 0;
	}

	info.stack_a = init_stack(argc, argv);
	info.stack_b = (t_list **)malloc(sizeof(t_list *));
	if (!info.stack_b)
		throw_error(info.stack_a, info.stack_b);
    *info.stack_b = NULL;

	// Display initial stack A
	printf("Initial Stack A:\n");
	print_list(*info.stack_a);

	// Test swap
	swap(info.stack_a);
	printf("After swap:\n");
	print_list(*info.stack_a);

	// Test push (push element from A to B)
	push(info.stack_b, info.stack_a);
	printf("After push from A to B:\n");
	printf("Stack A:\n");
	print_list(*info.stack_a);
	printf("Stack B:\n");
	print_list(*info.stack_b);

	// Test rotate
	rotate(info.stack_a);
	printf("After rotate A:\n");
	print_list(*info.stack_a);

	// Test reverse rotate
	reverse_rotate(info.stack_a);
	printf("After reverse rotate A:\n");
	print_list(*info.stack_a);

	// Free the memory
	ft_lstclear(info.stack_a);
	ft_lstclear(info.stack_b);

	return 0;
}