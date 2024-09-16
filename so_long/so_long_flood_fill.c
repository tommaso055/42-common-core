#include "so_long.h"

void terminate_program(game *mygame, point *entrance)
{
	free(entrance);
	while(mygame->rows--)
	{
		free(mygame->visited[mygame->rows]);
		free(mygame->map[mygame->rows]);
	}
	free(mygame->visited);
	free(mygame->map);
}

void throw_error(game *mygame, point *entrance)
{
	printf("%s", "there was a mistake");
	terminate_program(mygame, entrance);
}

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

char	**init_map(char *file_name, game *mygame)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(file_name, O_RDONLY);
	mygame->map = (char **)malloc(mygame->rows * sizeof(char *));
	while (i < mygame->rows )
	{
		mygame->map[i] = get_next_line(fd);
		if (ft_strlen(mygame->map[i]) != (mygame->columns - 1))
			mygame->checks++;
		i++;
	}
	close (fd);
	mygame->visited = init_zeroes(mygame->rows, mygame->columns);
	return (mygame->map);
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
			else if (c != WALL && c != EMPTY && c != COLLECTIBLE && c != ENTRANCE && c != EXIT)
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

point *get_info(char *file_name, game *mygame, int column)
{
	point	*entrance;
	int		fd;
	char	*line;

	entrance = NULL;
	fd = open (file_name, O_RDONLY);
	line = get_next_line(fd);
	mygame->columns = ft_strlen(line) - 1;
	while (line) // potrebbero servire controlli extra
	{
		while (line[column] && line[column] != '\n')
		{
			if (line[column] == ENTRANCE && mygame->n_entrances++ == 0)
				entrance = ft_lstnew(mygame->rows, column);
			if (line[column] == COLLECTIBLE)
				(mygame->n_collectibles)++;
			if (line[column++] == EXIT)
				(mygame->n_exits)++;
		}
		free(line);
		mygame->rows++;
		line = get_next_line(fd);
	}
	close(fd);
	return (entrance);
}

void set_up(game *mygame)
{
	mygame->n_collectibles = 0;
	mygame->n_entrances = 0;
	mygame->rows = 0;
	mygame->n_exits = 0;
    mygame->checks = 0;
    mygame->reachable_collectibles = 0;
}

int main(int argc, char **argv)
{
	game	mygame;
	point	*entrance; 
	
	set_up(&mygame);
	entrance = get_info(argv[1], &mygame, 0);
	init_map(argv[1], &mygame);
	if (mygame.n_entrances != 1 || mygame.n_exits != 1 || mygame.checks > 0)
	{
		throw_error(&mygame, entrance);
		return (0);
	}
	if (!is_valid(&mygame, ft_lstnew(entrance->row, entrance->column)))
	{
		throw_error(&mygame, entrance);
		return (0);
	}
	// play game
	terminate_program(&mygame, entrance);
	return(0);
}