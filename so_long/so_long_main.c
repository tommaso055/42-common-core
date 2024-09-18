#include "so_long.h"

char	**init_map(char *file_name, t_game *mygame)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(file_name, O_RDONLY);
	mygame->map = (char **)malloc(mygame->rows * sizeof(char *));
	while (i < mygame->rows )
	{
		mygame->map[i] = get_next_line(fd);
		if (ft_strlen(mygame->map[i]) != (mygame->columns + 1))
			if(ft_strlen(mygame->map[i]) != (mygame->columns) || get_next_line(fd))
				mygame->checks++;
		i++;
	}
	close (fd);
	mygame->visited = init_zeroes(mygame->rows, mygame->columns);
	return (mygame->map);
}

t_point *get_info(char *file_name, t_game *mygame, int column)
{
	t_point	*entrance;
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
		column = 0;
	}
	close(fd);
	return (entrance);
}

void set_up(t_game *mygame)
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
	t_game	mygame;
	t_point	*entrance; 
	
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
	play(&mygame, entrance);
	terminate_program(&mygame, entrance);
	return(0);
}