#include "so_long.h"

void	add_neighbors(point **curr, game *mygame)
{
	int i;
	int j;
	
	i = (*curr)->row;
	j = (*curr)->column;
	if(i-1 >= 0 && mygame->map[i-1][j] != WALL && mygame->visited[i-1][j] == 0)
	{
		ft_lstadd_back(curr, ft_lstnew(i-1, j));
		curr = &((*curr)->next);
	}
	if(i+1 < mygame->rows && mygame->map[i+1][j] != WALL && mygame->visited[i+1][j] == 0)
	{
		ft_lstadd_back(curr, ft_lstnew(i+1, j));
		curr = &((*curr)->next);
	}
	if(j-1 >= 0 && mygame->map[i][j-1] != WALL && mygame->visited[i][j-1] == 0)
	{
		ft_lstadd_back(curr, ft_lstnew(i, j-1));
		curr = &((*curr)->next);
	}
	if(j+1 < mygame->columns && mygame->map[i][j+1] != WALL && mygame->visited[i][j+1] == 0)
	{
		ft_lstadd_back(curr, ft_lstnew(i, j+1));
		curr = &((*curr)->next);
	}
}

void	set_visited(point *curr, game *mygame)
{
	int i;
	int j;
	
	i = curr->row;
	j = curr->column;
	if(i-1 >= 0 && mygame->map[i-1][j] != WALL && mygame->visited[i-1][j] == 0)
		mygame->visited[i-1][j]++;

	if(i+1 < mygame->rows && mygame->map[i+1][j] != WALL && mygame->visited[i+1][j] == 0)
		mygame->visited[i+1][j]++;
	if(j-1 >= 0 && mygame->map[i][j-1] != WALL && mygame->visited[i][j-1] == 0)
		mygame->visited[i][j-1]++;
	if(j+1 < mygame->columns && mygame->map[i][j+1] != WALL && mygame->visited[i][j+1] == 0)
		mygame->visited[i][j+1]++;
}

void	next_curr(point **lst)
{
	point	*temp;

	temp = (*lst)->next;
	free(*lst);
	*lst = temp;
}

int check_perimeter_and_chars(game *mygame, int i, int j)
{
	char c;

	while(i < mygame->rows)
	{
		while (j < mygame->columns)
		{
			c = mygame->map[i][j];
			if (i == 0 || i == mygame->rows - 1 || j == 0 || j == mygame->columns - 1)
				if (c != WALL)
					return (0);
			if (c != WALL && c != EMPTY && c != COLLECTIBLE && c != ENTRANCE && c != EXIT)
				return (0);
			j++;
		}
		i++;
		j = 0;
	}
	return (1);
}

int is_valid(game *mygame, point *curr)
{
	if (!check_perimeter_and_chars(mygame, 0, 0))
		return (0);
	mygame->visited[curr->row][curr->column]++;
	while (curr)
	{
		if (mygame->map[curr->row][curr->column] == COLLECTIBLE)
			mygame->reachable_collectibles++;
		if (mygame->map[curr->row][curr->column] == EXIT)
			mygame->checks++;
		add_neighbors(&curr, mygame);
		set_visited(curr, mygame);
		next_curr(&curr);
	}
	if (mygame->reachable_collectibles < mygame->n_collectibles || mygame->checks != 1)
		return (0);
	return (1);
}