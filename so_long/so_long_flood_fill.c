#include "so_long.h"

void throw_error(game *mygame, point *entrance)
{
	printf("%s", "there was a mistake");
	terminate_program(mygame, entrance);
}

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
	if(j+1 < mygame->cols && mygame->map[i][j+1] != WALL && mygame->visited[i][j+1] == 0)
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
	if(j+1 < mygame->cols && mygame->map[i][j+1] != WALL && mygame->visited[i][j+1] == 0)
		mygame->visited[i][j+1]++;
}

void	next_curr(point **lst)
{
	point	*temp;

	temp = (*lst)->next;
	free(*lst);
	*lst = temp;
}

int is_valid(game *mygame, point *curr)
{
	mygame->visited = init_zeroes(rows, columns);
	mygame->visited[curr->row][curr->column]++;
	while (curr)
	{
		add_neighbors(&curr, mygame);
		set_visited(curr, mygame);
		next_curr(&curr);
	}
}

char	**init_map(char *file_name, game *mygame)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(file_name, O_RDONLY);
	mygame->map = (char **)malloc(mygame->rows * sizeof(char *));
	while (i < mygame->rows ) 
		mygame->map[i++] = get_next_line(fd);
	close (fd);
	return (mygame->map);
}

point *get_info(char *file_name, game *mygame, int column)
{
	point	*entrance;
	int		fd;
	char	*line;

	entrance = NULL;
	fd = open (file_name, O_RDONLY);
	line = get_next_line(fd);
	mygame->cols = ft_strlen(line) - 1;
	while (line) // potrebbero servire controlli extra
	{
		while (line[column] && line[column] != '\n')
		{
			if (line[column] == ENTRANCE && mygame->n_entrances++ == 0)
				entrance = ft_lstnew(row, column);
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

int main(int argc, char **argv)
{
	game	mygame;
	point	*entrance; 
	
	mygame.n_collectibles = 0;
	mygame.n_entrances = 0;         // potresti dover inizializzare anche gli altri parametri
	mygame.rows = 0;
	mygame.n_exits = 0;

	entrance = get_info(argv[1], &mygame, 0);
	if (mygame.n_entrances != 1 || mygame.n_exits != 1)
	{
		throw_error(&mygame, entrance);
		return (-1);
	}

	if (!init_map(argv[1], &mygame)) // controlla rettangolo

	if (!is_valid(&mygame, ft_lstnew(entrance->row, entrance->column)))
	{
		throw_error(&mygame, entrance);
		return (-1);
	}
	// play game
	terminate_program(&mygame, entrance);
	return(0);
}

// okkkkkk


// rettangolo
// perimetro
// all collectibles