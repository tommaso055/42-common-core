/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:30:07 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/18 17:30:10 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	terminate_program(t_game *mg, t_point *entrance)
{
	free(entrance);
	while (mg->rows--)
	{
		free(mg->vis[mg->rows]);
		free(mg->map[mg->rows]);
	}
	free(mg->vis);
	free(mg->map);
}

void	throw_error(t_game *mg, t_point *entrance)
{
	ft_printf("%s", "Error\nINVALID MAP");
	terminate_program(mg, entrance);
}

t_point	*ft_lstnew(int row, int column)
{
	t_point	*list;

	list = (t_point *)malloc(sizeof(t_point));
	if (!list)
		return (NULL);
	list->next = NULL;
	list->row = row;
	list->column = column;
	return (list);
}

void	ft_lstadd_back(t_point **lst, t_point *new)
{
	t_point	*curr;

	if (!new)
		return ;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	curr = *lst;
	while (curr->next)
		curr = curr->next;
	curr->next = new;
}

int	**init_zeroes(int rows, int columns)
{
	int	**array;
	int	i;
	int	j;

	i = -1;
	j = -1;
	array = malloc(sizeof(int *) * rows);
	while (++i < rows)
	{
		array[i] = malloc(sizeof(int) * columns);
		while (++j < columns)
			array[i][j] = 0;
		j = -1;
	}
	return (array);
}
