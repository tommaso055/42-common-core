#include "push_swap.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*curr;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		curr = *lst;
		*lst = curr->next;
		free(curr);
	}
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	ans;

	i = 0;
	sign = 1;
	ans = 0;
	while (str[i] == ' ' || (9 <= str[i] && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ('0' <= str[i] && str[i] <= '9')
	{
		ans = ans * 10 + str[i] - 48;
		i++;
	}
	return (ans * sign);
}

t_list	*ft_lstnew(int content)
{
	t_list	*list;

	list = (t_list *)malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->next = NULL;
	list->content = content;
	return (list);
}

void	throw_error(t_list **head)
{
	
	ft_lstclear(head);
	exit(1);
}

t_list	**init_stack(int argc, char **argv)
{
	int		i;
	t_list	**head;
	t_list	*last;
	int		n;

	head = (t_list **)malloc(sizeof(t_list *));
	if (!head)
		throw_error(NULL);
	i = 1;
	n = ft_atoi(argv[i]);
	if (!n && argv[i] != "0")
		throw_error(head);
	*head = ft_lstnew(n);
	last = (*head);
	while(++i < argc)
	{
		n = ft_atoi(argv[i]);
		if (!n && argv[i][0] != '0')
			throw_error(head);
		last->next = ft_lstnew(n);
		last = last->next;
	}
	return (head);
}

void	swap(t_list **head)
{
	t_list *temp;

    if (*head == NULL || (*head)->next == NULL)
        return ;
	temp = (*head)->next;
    (*head)->next = temp->next;
	temp->next = (*head);
    *head = temp;
}

void	push(t_list **target, t_list **source)
{
	t_list  *temp;

	if (*source == NULL)
        return ;
	temp = (*source);
	(*source) = temp->next;
	temp->next = *target;
	*target = temp;
}

void	reverse_rotate(t_list **head)
{
	t_list *new_tail;

    if (*head == NULL || (*head)->next == NULL)
        return ;
	new_tail = *head;
    while (new_tail->next->next != NULL)
        new_tail = new_tail->next;
    new_tail->next->next = *head;
	*head = new_tail->next;
    new_tail->next = NULL;
}

void	rotate(t_list **head)
{
	t_list  *tail;

    if (*head == NULL || (*head)->next == NULL)
        return ;
	tail = *head;
	while(tail->next != NULL)
		tail = tail->next;
	tail->next = *head;
	*head = (*head)->next;
	tail->next->next = NULL;
	return ;
} 

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
	t_list **stack_a;
	t_list *stack_b = NULL;

	if (argc < 2)
	{
		printf("Usage: ./a.out [numbers...]\n");
		return 0;
	}

	// Initialize stack A
	stack_a = init_stack(argc, argv);

	// Display initial stack A
	printf("Initial Stack A:\n");
	print_list(*stack_a);

	// Test swap
	swap(stack_a);
	printf("After swap:\n");
	print_list(*stack_a);

	// Test push (push element from A to B)
	push(&stack_b, stack_a);
	printf("After push from A to B:\n");
	printf("Stack A:\n");
	print_list(*stack_a);
	printf("Stack B:\n");
	print_list(stack_b);

	// Test rotate
	rotate(stack_a);
	printf("After rotate A:\n");
	print_list(*stack_a);

	// Test reverse rotate
	reverse_rotate(stack_a);
	printf("After reverse rotate A:\n");
	print_list(*stack_a);

	// Free the memory
	ft_lstclear(stack_a);
	free(stack_a);
	ft_lstclear(&stack_b);

	return 0;
}