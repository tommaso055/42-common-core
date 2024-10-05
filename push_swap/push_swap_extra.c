/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_extra.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 20:00:16 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/24 20:00:20 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	max(int a, int b)
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

void	main_controls(t_push_swap *info)
{
	if (!info->stack_b)
		terminate(info->stack_a, info->stack_b, "Error\n");
	*info->stack_b = NULL;
	if (find_length(info->stack_a) < 2)
		terminate(info->stack_a, info->stack_b, NULL);
	if (check_duplicates(info->stack_a))
		terminate(info->stack_a, info->stack_b, "Error\n");
	if (info->length_a == 2)
	{
		solve_two(info);
		terminate(info->stack_a, info->stack_b, NULL);
	}
	if (info->length_a == 3)
		solve_three(info);
	if (in_order(info->stack_a))
		terminate(info->stack_a, info->stack_b, NULL);
}

int	ft_matrixlen(char **s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

