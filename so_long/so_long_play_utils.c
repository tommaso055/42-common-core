#include "so_long.h"

void	set_up_sprites(t_bank *data, t_sprites *info, int size)
{
	info->grass = mlx_xpm_file_to_image(data->xvar, GRASS, &size, &size);
	info->stone = mlx_xpm_file_to_image(data->xvar, STONE, &size, &size);
	info->book = mlx_xpm_file_to_image(data->xvar, BOOK, &size, &size);
	info->vortex = mlx_xpm_file_to_image(data->xvar, VORTEX, &size, &size);
	info->player = mlx_xpm_file_to_image(data->xvar, PLAYER, &size, &size);
	info->player_exit = mlx_xpm_file_to_image(data->xvar, PLAYER_EXIT, &size, &size);
}

void	destroy_sprites(t_bank *data)
{
	mlx_destroy_image(data->xvar, data->info.grass);
	mlx_destroy_image(data->xvar, data->info.stone);
	mlx_destroy_image(data->xvar, data->info.book);
	mlx_destroy_image(data->xvar, data->info.vortex);
	mlx_destroy_image(data->xvar, data->info.player);
	mlx_destroy_image(data->xvar, data->info.player_exit);
}

void	put_map(t_bank *data, t_sprites *info, int i, int j)
{
	int	size;

	size = TILE_SIZE;
	while (i < data->mygame->rows)
	{
		while (j < data->mygame->columns)
		{
			if (data->mygame->map[i][j] == WALL)
				mlx_put_image_to_window(data->xvar, data->window, info->stone, j * 128, i * 128);
			if (data->mygame->map[i][j] == ENTRANCE)
				mlx_put_image_to_window(data->xvar, data->window, info->player, j * 128, i * 128);
			if (data->mygame->map[i][j] == COLLECTIBLE)
				mlx_put_image_to_window(data->xvar, data->window, info->book, j * 128, i * 128);
			if (data->mygame->map[i][j] == EXIT)
				mlx_put_image_to_window(data->xvar, data->window, info->vortex, j * 128, i * 128);
			if (data->mygame->map[i][j] == EMPTY)
				mlx_put_image_to_window(data->xvar, data->window, info->grass, j * 128, i * 128);
			if (data->mygame->map[i][j] == 'F')
				mlx_put_image_to_window(data->xvar, data->window, info->player_exit, j * 128, i * 128);
			j++;
		}
		i++;
		j = 0;
	}
}

void	convert_to_move(int keysim, int *dr, int *dc)
{
	if (keysim == XK_w)
		(*dc)--;
	if (keysim == XK_a)
		(*dr)--;
	if (keysim == XK_s)
		(*dc)++;
	if (keysim == XK_d)
		(*dr)++;
}

void	move(int dr, int dc, t_bank *data)
{
	if (data->mygame->map[data->position->row + dc][data->position->column + dr] != WALL)
	{
		if (data->mygame->map[data->position->row][data->position->column] == 'F')
			data->mygame->map[data->position->row][data->position->column] = EXIT;
		else
			data->mygame->map[data->position->row][data->position->column] = EMPTY;
		if (data->mygame->map[data->position->row + dc][data->position->column + dr] == COLLECTIBLE)
			data->mygame->reachable_collectibles--;
		if (data->mygame->map[data->position->row + dc][data->position->column + dr] == EXIT)
		{
			if (!data->mygame->reachable_collectibles)
			{
				ft_printf("%s", "YOU WON!");
				key_pressed(XK_Escape, data);
			}
			data->mygame->map[data->position->row + dc][data->position->column + dr] = 'F';
		}
		else
			data->mygame->map[data->position->row + dc][data->position->column + dr] = ENTRANCE;
		data->position->row = data->position->row + dc;
		data->position->column = data->position->column + dr;
		data->mygame->move_counter++;
		ft_printf("You have moved %d times\n", data->mygame->move_counter);
	}
}
