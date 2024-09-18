#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include "get_next_line.h"
#include "ft_printf.h"

#define EMPTY '0'
#define WALL '1'
#define COLLECTIBLE 'C'
#define EXIT 'E'
#define ENTRANCE 'P'

#define BOOK "textures/Book.xpm"
#define STONE "textures/Stone.xpm"
#define GRASS "textures/Grass.xpm"
#define VORTEX "textures/Vortex.xpm"
#define PLAYER "textures/Player.xpm"
#define PLAYER_EXIT "textures/Player_Exit.xpm"
#define TILE_SIZE 128

typedef struct s_point
{
	struct s_point	*next;
	int				row;
	int				column;
}	t_point;

typedef struct s_game
{
	char	**map;
	int		**vis;
	int		columns;
	int		rows;
	int		n_collectibles;
	int		n_entrances;
	int		n_exits;
	int		checks;
	int		reachable_collectibles;
	int		move_counter;
}	t_game;

typedef struct s_sprites
{
	void	*grass;
	void	*stone;
	void	*book;
	void	*vortex;
	void	*player;
	void	*player_exit;
}	t_sprites;

typedef struct s_bank
{
	void		*xvar;
	void		*window;
	t_game		*mygame;
	t_point		*position;
	t_sprites	info;
}	t_bank;

t_point	*ft_lstnew(int row, int column);
void	ft_lstadd_back(t_point **lst, t_point *new);
int		**init_zeroes(int rows, int columns);
void	terminate_program(t_game *mygame, t_point *entrance);
void	throw_error(t_game *mygame, t_point *entrance);
int		key_pressed(int keysim, t_bank *param);
int		play(t_game *mygame, t_point *entrance);
char	**init_map(char *file_name, t_game *mygame);
t_point	*get_info(char *file_name, t_game *mygame, int column);
void	set_up(t_game *mygame);
int		main(int argc, char **argv);
void	add_neighbors(t_point **curr, t_game *mygame);
void	set_visited(t_point *curr, t_game *mygame);
void	next_curr(t_point **lst);
int		is_valid(t_game *mygame, t_point *curr);
void	move(int dx, int dy, t_bank *data);
void	set_up_sprites(t_bank *data, t_sprites *info, int size);
void	destroy_sprites(t_bank *data);
void	put_map(t_bank *data, t_sprites *info, int i, int j);
void	convert_to_move(int keysim, int *dx, int *dy);
int		handle_close(t_bank *data);
