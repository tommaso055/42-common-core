#include "so_long.h"

int get_info(char *file_name, point **entrance, game *mygame)
{
	int		fd;
	char	*line;
	int		row;
	int		column;

	row = 0;
	column = 0;
	fd = open (file_name, O_RDONLY);
	line = get_next_line(fd);
	mygame->cols = ft_strlen(line);
	while (line) // potrebbero servire controlli extra
	{
		while (line[column]) // potresti dover mettere ( != \n)
		{
			if (line[column] == SPAWN)
				*entrance = ft_lstnew(row, column);
			if (line[column] == COLLECTIBLE)
				(mygame->n_collectibles)++;
			column++;
		}
		free(line);
		row++;
		if (column != (mygame->cols + 1)) // non necessario? potresti metterlo all'inizio
			return (0);
		line = get_next_line(fd);
	}
	mygame->rows = row;
	close(fd);
	return (0);
}

char	**init_map(char *file_name, int rows)
{
	char	**map;
	int		i;
	int		fd;

	i = 0;
	fd = open(file_name, O_RDONLY);
	map = (char **)malloc(rows * sizeof(char *));
	while (i < rows ) 
		map[i++] = get_next_line(fd);
	close (fd);
	return (map);
}

void	add_neighbors(point **curr, int **visited, char **map, int rows, int columns) //funzione troppo lunga e con troppi argomenti
{
	int i;
	int j;
	
	i = (*curr)->row;
	j = (*curr)->column;
	if(i-1 >= 0 && map[i-1][j] != WALL && visited[i-1][j] == 0)
	{
		ft_lstadd_back(curr, ft_lstnew(i-1, j));
		curr = &((*curr)->next);
		visited[i-1][j]++;
	}
	if(i+1 < rows && map[i+1][j] != WALL && visited[i+1][j] == 0)
	{
		ft_lstadd_back(curr, ft_lstnew(i+1, j));
		curr = &((*curr)->next);
		visited[i+1][j]++;
	}
	if(j-1 >= 0 && map[i][j-1] != WALL && visited[i][j-1] == 0)
	{
		ft_lstadd_back(curr, ft_lstnew(i, j-1));
		curr = &((*curr)->next);
		visited[i][j-1]++;
	}
	if(j+1 < rows && map[i][j+1] != WALL && visited[i][j+1] == 0)
	{
		ft_lstadd_back(curr, ft_lstnew(i, j+1));
		curr = &((*curr)->next);
		visited[i][j+1]++;
	}
}

void	set_visited(point *curr, int **visited, int rows, int columns)
{
	if (curr->row + 1 < rows ); // && ...
}

int is_valid(char **map, int rows, int collectibles_number, point *curr)
{
	int columns;
	int **visited;

	columns = ft_strlen(map[0]) - 1;
	visited = init_zeroes(rows, columns);
	visited[curr->row][curr->column]++;
	while (curr)
	{
		add_neighbors(&curr, visited, map, rows, columns);
		//set_visited(curr, visited, rows, columns);
		next_curr(&curr);
	}
}

int main(int argc, char **argv)
{

	game	mygame;
	point	*entrance; // forse devi togliere il pointer
	
	
	entrance = malloc(sizeof(point));
	get_info(argv[1], &entrance, &mygame);
	if (mygame.cols == 0)
		return (0);
	mygame.map = init_map(argv[1], mygame.rows);
	// if (!is_valid(mygame.map, mygame.rows, mygame.n_collectibles, ft_lstnew(entrance->row, entrance->column)))
	// 	return (0);
    printf("%s", "daje funziona");
    return (0);
}