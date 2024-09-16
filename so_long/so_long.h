#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

#define EMPTY '0'
#define WALL '1'
#define COLLECTIBLE 'C'
#define EXIT 'E'
#define ENTRANCE 'P'

typedef struct bank {
    void *xvar;
    void *window;
} bank;

typedef struct point
{
	struct point	*next;
	int		row;
	int		column;
}	point;

typedef struct game
{
    char **map;
    int **visited;
    int cols;
    int rows;
    int n_collectibles;
    int n_entrances;
} game;

point	*ft_lstnew(int row, int column);
void	ft_lstadd_back(point **lst, point *new);
int	**init_zeroes(int rows, int columns);