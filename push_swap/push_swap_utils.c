#include "push_swap.h"

// int	find_max(t_list **head)
// {
// 	int		max;
// 	t_list	*curr;

// 	curr = *head;
// 	max = curr->content;
// 	while (curr->next)
// 	{
// 		curr = curr->next;
// 		if (curr->content > max)
// 			max = curr->content;
// 	}
// 	return (max);
// }

// int	find_min(t_list **head)
// {
// 	int		min;
// 	t_list	*curr;

// 	curr = *head;
// 	min = curr->content;
// 	while (curr->next)
// 	{
// 		curr = curr->next;
// 		if (curr->content < min)
// 			min = curr->content;
// 	}
// 	return (min);
// }

int max(int a, int b)
{
	if (b > a)
		return (b);
	return (a);
}

int	min(int a, int b, int c, int d)
{
	if (d < a && d < b && d < c)
		return (d);
	if (c < a && c < b && c < d)
		return (c);
	if (b < a && b < c && b < d)
		return (b);
	return (a);
}

int	find_length(t_list **head)
{
	int		length;
	t_list	*curr;

	if (!head || !*head)
		return (0);
	length = 1;
	curr = *head;
	while (curr->next)
	{
		curr = curr->next;
		length++;
	}
	return (length);
}

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
    free(lst);
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

void	terminate(t_list **stack_a, t_list **stack_b)
{
	ft_lstclear(stack_a);
    ft_lstclear(stack_a);
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
		terminate(NULL, NULL);
	i = 1;
	n = ft_atoi(argv[i]);
	if (!n && argv[i][0] != '0')
		terminate(head, NULL);
	*head = ft_lstnew(n);
	last = (*head);
	while(++i < argc)
	{
		n = ft_atoi(argv[i]);
		if (!n && argv[i][0] != '0')
			terminate(head, NULL);
		last->next = ft_lstnew(n);
		if (!(last->next))
			terminate(head, NULL);
		last = last->next;
	}
	return (head);
}

