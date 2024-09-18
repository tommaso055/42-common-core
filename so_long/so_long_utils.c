#include "so_long.h"

void	terminate_program(t_game *mygame, t_point *entrance)
{
	free(entrance);
	while (mygame->rows--)
	{
		free(mygame->vis[mygame->rows]);
		free(mygame->map[mygame->rows]);
	}
	free(mygame->vis);
	free(mygame->map);
}

void	throw_error(t_game *mygame, t_point *entrance)
{
	ft_printf("%s", "Error\nINCORRECT MAP FORMAT");
	terminate_program(mygame, entrance);
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
