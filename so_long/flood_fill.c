#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


#define EMPTY '0'
#define WALL '1'
#define COLLECTIBLE 'C'
#define EXIT 'E'
#define SPAWN 'S'

typedef struct point
{
	point	*next;
	int		row;
	int		column;
}	point;

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

int get_info(char *file_name, point **entrance, int *collectibles_number, int *rows)
{
	int		fd;
	char	*line;
	int		row;
	int		column;
	int		columns;

	row = 0;
	column = 0;
	fd = open (file_name, O_RDONLY);
	line = get_next_line(fd);
	columns = ft_len(line) - 1;
	while (line) // potrebbero servire controlli extra
	{
		while (line[column]) // potresti dover mettere ( != \n)
		{
			if (line[column] == SPAWN)
				*entrance = ft_lstnew(row, column);
			if (line[column] == COLLECTIBLE)
				(*collectibles_number)++;
			column++;
		}
		free(line);
		row++;
		if (column != (columns + 1)) // non necessario? potresti metterlo all'inizio
			return (0);
		line = get_next_line(fd);
	}
	*rows = row;
	close(fd);
	return (columns);
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

void	next_curr(point **lst)
{
	point	*temp;

	temp = (*lst)->next;
	free(*lst);
	*lst = temp;
}

void	set_visited(point *curr, int **visited, int rows, int columns)
{
	if (curr->row + 1 < rows ); // && ...
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

int is_valid(char **map, int rows, int collectibles_number, point *curr)
{
	int columns;
	int **visited;

	columns = ft_len(map[0]) - 1;
	visited = init_zeroes(rows, columns);
	visited[curr->row][curr->column]++;
	while (curr)
	{
		// add neighbors to list
		add_neighbors(&curr, visited, map, rows, columns);
		// set neighbors as visited
		set_visited(curr, visited, rows, columns);
		// set curr to next
		next_curr(&curr);
	}
}

int main(int argc, char **argv)
{
	point	*entrance;
	char	**map;
	int		rows;
	int		columns;
	int		collectibles_number;
	
	
	columns = get_info(argv[1], &entrance, &collectibles_number, &rows);
	if (columns == 0)
		return (0);
	map = init_map(argv[1], rows);
	if (!is_valid(map, rows, collectibles_number, ft_lstnew(entrance->row, entrance->column)))
		return (0);

}