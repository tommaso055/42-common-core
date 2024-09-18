/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_flood_fill.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:30:07 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/18 17:30:10 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	add_neighbors(t_point **curr, t_game *mg)
{
	int	i;
	int	j;

	i = (*curr)->row;
	j = (*curr)->column;
	if (i - 1 >= 0 && mg->map[i - 1][j] != WALL && mg->vis[i - 1][j] == 0)
	{
		ft_lstadd_back(curr, ft_lstnew(i - 1, j));
		curr = &((*curr)->next);
	}
	if (i + 1 < mg->rows && mg->map[i + 1][j] != WALL && mg->vis[i + 1][j] == 0)
	{
		ft_lstadd_back(curr, ft_lstnew(i + 1, j));
		curr = &((*curr)->next);
	}
	if (j - 1 >= 0 && mg->map[i][j - 1] != WALL && mg->vis[i][j - 1] == 0)
	{
		ft_lstadd_back(curr, ft_lstnew(i, j - 1));
		curr = &((*curr)->next);
	}
	if (j + 1 < mg->cols && mg->map[i][j + 1] != WALL && mg->vis[i][j + 1] == 0)
	{
		ft_lstadd_back(curr, ft_lstnew(i, j + 1));
		curr = &((*curr)->next);
	}
}

void	set_visited(t_point *curr, t_game *mg)
{
	int	i;
	int	j;

	i = curr->row;
	j = curr->column;
	if (i - 1 >= 0 && mg->map[i - 1][j] != WALL && mg->vis[i - 1][j] == 0)
		mg->vis[i - 1][j]++;
	if (i + 1 < mg->rows && mg->map[i + 1][j] != WALL && mg->vis[i + 1][j] == 0)
		mg->vis[i + 1][j]++;
	if (j - 1 >= 0 && mg->map[i][j - 1] != WALL && mg->vis[i][j - 1] == 0)
		mg->vis[i][j - 1]++;
	if (j + 1 < mg->cols && mg->map[i][j + 1] != WALL && mg->vis[i][j + 1] == 0)
		mg->vis[i][j + 1]++;
}

void	next_curr(t_point **lst)
{
	t_point	*temp;

	temp = (*lst)->next;
	free(*lst);
	*lst = temp;
}

int	check_perimeter_and_chars(t_game *mg, int i, int j)
{
	char	c;

	while (i < mg->rows)
	{
		while (j < mg->cols)
		{
			c = mg->map[i][j];
			if (i == 0 || i == mg->rows - 1 || j == 0 || j == mg->cols - 1)
				if (c != WALL)
					return (0);
			if (c != WALL && c != EMPTY && c != COLL && c != ENTR && c != EXIT)
				return (0);
			j++;
		}
		i++;
		j = 0;
	}
	return (1);
}

int	is_valid(t_game *mg, t_point *curr)
{
	if (!check_perimeter_and_chars(mg, 0, 0))
		return (0);
	mg->vis[curr->row][curr->column]++;
	while (curr)
	{
		if (mg->map[curr->row][curr->column] == COLL)
			mg->reachable_coll++;
		if (mg->map[curr->row][curr->column] == EXIT)
			mg->checks++;
		add_neighbors(&curr, mg);
		set_visited(curr, mg);
		next_curr(&curr);
	}
	if (mg->reachable_coll < mg->n_coll || mg->checks != 1)
		return (0);
	return (1);
}
