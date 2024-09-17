#include "so_long.h"

int key_pressed(int keysim, bank *data)
{

    if (keysim == XK_Escape) // || keysim == X)
    {
        mlx_destroy_window(data->xvar, data->window);
        mlx_destroy_display(data->xvar);
        free(data->xvar);
        terminate_program(data->mygame, data->position);
        exit(0);
    }
    if (keysim == XK_w || keysim == XK_a || keysim == XK_s || keysim == XK_d)
        move(keysim, data);
    return (0);
}

int move(int keysim, bank *data)
{

}

void put_map(bank *data)
{
    int i;
    int j;
    void *grass;
    void *stone;
    void *book;
    void *vortex;
    void *player;
    int size = TILE_SIZE;

    i = 0;
    j = 0;
    grass = mlx_xpm_file_to_image(data->xvar, GRASS, &size, &size);
    stone = mlx_xpm_file_to_image(data->xvar, STONE, &size, &size);
    book = mlx_xpm_file_to_image(data->xvar, BOOK, &size, &size);
    vortex = mlx_xpm_file_to_image(data->xvar, VORTEX, &size, &size);
    player = mlx_xpm_file_to_image(data->xvar, PLAYER, &size, &size);
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
}

int play(game *mygame, point *entrance)
{
    bank data;
    void *pointer;
    int size = TILE_SIZE;

    data.position = entrance;
    data.mygame = mygame;
    data.xvar = mlx_init();
    data.window = mlx_new_window(data.xvar, mygame->columns * 128, mygame->rows * 128, "titolo");
    mlx_key_hook(data.window, key_pressed, &data);

    put_map(&data);

    mlx_loop(data.xvar);
    return (0);
}