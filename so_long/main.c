#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define COLLECTIBLES 1
#define EXIT 3
#define SPAWN 2

typedef struct object
{
	int     row;
	int     column;
}   object;

int *read_map(char *file_name, int fd, object *entrance, int *n_collectibles)
{
	char    *line;
	int     row;
	int     column;
	int     n_lines;

	row = 0;
	column = 0;
	n_lines = 0;
	fd = open (file_name, O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		while (line[column])
		{
			if (line[column] == '\n')
				n_lines++;
			if (line[column] == 'P')
			{
				(*entrance).column = column;
				(*entrance).row = row;
			}
			if (line[column] == 'C')
				(*n_collectibles)++;
			column++;
		}
		free(line);
		row++;
	}
}

char    **init_map(char *file_name)
{
	char    **map;
	int     i;
	int     fd;
	int     *useful_num;

	i = 0;
	useful_num = read_map(file_name, 0);
	fd = open(file_name, O_RDONLY);
	map = (char **)malloc(useful_num[0]*sizeof(char *));
	while (i < useful_num[0])
		map[i++] = get_next_line(fd);
	close (fd);
	return (map);
}

int is_valid(char **map)
{

}

int main(int argc, char **argv)
{
	object   entrance;
	char    **map;
	int     n_lines;
	int     n_collectibles;
	
	n_lines = 0;
	if (argc == 2)
	{
		n_lines = read_map(argv[1], 0, &entrance, &n_collectibles);
		map = init_map(argv[1]);
		if (!is_valid(map))
			return (0);
	}
	else
		ft_printf("Input errato");
	return (0);
}