/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:00:52 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/24 20:00:54 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	ft_lstclear(t_list **lst)
{
	t_list	*curr;

	if (lst == NULL)
		return ;
	while (*lst != NULL)
	{
		curr = (*lst)->next;
		free(*lst);
		*lst = curr;
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

void	terminate(t_list **stack_a, t_list **stack_b, char *str)
{
	if (str)
		put_str(str);
	ft_lstclear(stack_a);
	ft_lstclear(stack_b);
	exit(1);
}

t_list	**init_stack(int argc, char **argv, int start)
{
	int		i;
	t_list	**head;
	t_list	*last;
	int		n;

	head = (t_list **)malloc(sizeof(t_list *));
	if (!head)
		terminate(NULL, NULL, "Error\nMalloc error");
	i = start;
	n = ft_atoi(argv[i]);
	if (!n && (argv[i][0] != '0' || argv[i][1] != '\0'))
		terminate(head, NULL, "Error\nInvalid input");
	*head = ft_lstnew(n);
	last = (*head);
	while (++i < argc)
	{
		n = ft_atoi(argv[i]);
		if (!n && (argv[i][0] != '0' || argv[i][1] != '\0'))
			terminate(head, NULL, "Error\nInvalid input");
		last->next = ft_lstnew(n);
		if (!(last->next))
			terminate(head, NULL, "Error\nMalloc error");
		last = last->next;
	}
	return (head);
}