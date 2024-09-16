#include "so_long.h"

point	*ft_lstnew(int row, int column)
{
	point	*list;

	list = (point *)malloc(sizeof(point));
	if (!list)
		return (NULL);
	list->next = NULL;
	list->row = row;
	list->column = column;
	return (list);
}

void	ft_lstadd_back(point **lst, point *new)
{
	point	*curr;

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
	int **array;
	int i;
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
