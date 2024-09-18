#include "so_long.h"

void put_map(t_bank *data, int i, int j)
{
    int size;
    void *grass;
    void *stone;
    void *book;
    void *vortex;
    void *player;
    void *player_exit;

    size = TILE_SIZE;
    grass = mlx_xpm_file_to_image(data->xvar, GRASS, &size, &size);
    stone = mlx_xpm_file_to_image(data->xvar, STONE, &size, &size);
    book = mlx_xpm_file_to_image(data->xvar, BOOK, &size, &size);
    vortex = mlx_xpm_file_to_image(data->xvar, VORTEX, &size, &size);
    player = mlx_xpm_file_to_image(data->xvar, PLAYER, &size, &size);
    player_exit = mlx_xpm_file_to_image(data->xvar, PLAYER_EXIT, &size, &size);
	while(i < data->mygame->rows)
	{
		while (j < data->mygame->columns)
		{
			if (data->mygame->map[i][j] == WALL)
                mlx_put_image_to_window(data->xvar, data->window, stone, j * 128, i * 128);
            if (data->mygame->map[i][j] == ENTRANCE)
                mlx_put_image_to_window(data->xvar, data->window, player, j * 128, i * 128);
            if (data->mygame->map[i][j] == COLLECTIBLE)
                mlx_put_image_to_window(data->xvar, data->window, book, j * 128, i * 128);
            if (data->mygame->map[i][j] == EXIT)
                mlx_put_image_to_window(data->xvar, data->window, vortex, j * 128, i * 128);
            if (data->mygame->map[i][j] == EMPTY)
                mlx_put_image_to_window(data->xvar, data->window, grass, j * 128, i * 128);
            if (data->mygame->map[i][j] == 'F')
                mlx_put_image_to_window(data->xvar, data->window, player_exit, j * 128, i * 128);
			j++;
		}
		i++;
		j = 0;
	}
    mlx_destroy_image(data->xvar, grass);
    mlx_destroy_image(data->xvar, stone);
    mlx_destroy_image(data->xvar, book);
    mlx_destroy_image(data->xvar, vortex);
    mlx_destroy_image(data->xvar, player);
    mlx_destroy_image(data->xvar, player_exit);

}

void convert_to_move(int keysim, int *dr, int *dc)
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

int move(int dr, int dc, t_bank *data)
{
    int curr_row;
    int curr_column;

    curr_row = data->position->row;
    curr_column = data->position->column;
    if (data->mygame->map[curr_row + dc][curr_column + dr] != '1')
    {
        if (data->mygame->map[curr_row][curr_column] == 'F')
            data->mygame->map[curr_row][curr_column] = 'E';
        else
            data->mygame->map[curr_row][curr_column] = '0';
        if (data->mygame->map[curr_row + dc][curr_column + dr] == 'C')
            data->mygame->reachable_collectibles--;
        if (data->mygame->map[curr_row + dc][curr_column + dr] == 'E')
        {
            if (!data->mygame->reachable_collectibles)
            {
                key_pressed(XK_Escape, data);
                return (0);
            }
            data->mygame->map[curr_row + dc][curr_column + dr] = 'F';
        }
        else
            data->mygame->map[curr_row + dc][curr_column + dr] = 'P';
        data->position->row = curr_row + dc;
        data->position->column = curr_column + dr;
    }
    return (0);
}


int key_pressed(int keysim, t_bank *data)
{
    int dx;
    int dy;

    dx = 0;
    dy = 0;
    if (keysim == XK_w || keysim == XK_a || keysim == XK_s || keysim == XK_d)
    {
        convert_to_move(keysim, &dx, &dy);
        move(dx, dy, data);
        put_map(data, 0, 0);
    }
    if (keysim == XK_Escape)
    {
        mlx_destroy_window(data->xvar, data->window);
        mlx_destroy_display(data->xvar);
        free(data->xvar);
        terminate_program(data->mygame, data->position);
        exit(0);
    }
    return (0);
}

int handle_close(t_bank *data)
{
    key_pressed(XK_Escape, data);
    return (0);
}

int play(t_game *mygame, t_point *entrance)
{
    t_bank data;
    void *pointer;

    data.position = entrance;
    data.mygame = mygame;
    data.xvar = mlx_init();
    data.window = mlx_new_window(data.xvar, mygame->columns * 128, mygame->rows * 128, "titolo");
    mlx_key_hook(data.window, key_pressed, &data);
    mlx_hook(data.window, 17, 0, handle_close, &data);

    put_map(&data, 0, 0);

    mlx_loop(data.xvar);
    return (0);
}
















// void set_up_sprites(t_bank *data, int size)
// {
//     data->info->grass = mlx_xpm_file_to_image(data->xvar, GRASS, &size, &size);
//     data->info->stone = mlx_xpm_file_to_image(data->xvar, STONE, &size, &size);
//     data->info->book = mlx_xpm_file_to_image(data->xvar, BOOK, &size, &size);
//     data->info->vortex = mlx_xpm_file_to_image(data->xvar, VORTEX, &size, &size);
//     data->info->player = mlx_xpm_file_to_image(data->xvar, PLAYER, &size, &size);
// }

// void destroy_sprites(t_bank *data)
// {
//     mlx_destroy_image(data->xvar, data->info->grass);
//     mlx_destroy_image(data->xvar, data->info->stone);
//     mlx_destroy_image(data->xvar, data->info->book);
//     mlx_destroy_image(data->xvar, data->info->vortex);
//     mlx_destroy_image(data->xvar, data->info->player);
// }