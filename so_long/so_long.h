#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include "get_next_line.h"

#define EMPTY '0'
#define WALL '1'
#define COLLECTIBLE 'C'
#define EXIT 'E'
#define SPAWN 'P'

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
    char **visited;
    int cols;
    int rows;
    int n_collectibles;
} game;

point	*ft_lstnew(int row, int column);
void	ft_lstadd_back(point **lst, point *new);
int	**init_zeroes(int rows, int columns);