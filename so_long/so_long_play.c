#include "so_long.h"

int key_pressed(int keysim, bank *param)
{

    if (keysim == XK_Escape)
    {
        mlx_destroy_window(param->xvar, param->window);
        mlx_destroy_display(param->xvar);
        free(param->xvar);
        terminate_program(param->mygame);
        exit(0);
    }
    return (0);
}

void put_map(bank *data)
{
    int i;
    int j;
    void *lava;
    void *stone;
    int size = TILE_SIZE;

    i = 0;
    j = 0;
    lava = mlx_xpm_file_to_image(data->xvar, LAVA, &size, &size);
    stone = mlx_xpm_file_to_image(data->xvar, STONE, &size, &size);
	while(i < data->mygame->rows)
	{
		while (j < data->mygame->columns)
		{
			if (data->mygame->map[i][j] == WALL)
                mlx_put_image_to_window(data->xvar, data->window, lava, j * 128, i * 128);
            else
                mlx_put_image_to_window(data->xvar, data->window, stone, j * 128, i * 128);
			j++;
		}
		i++;
		j = 0;
	}
}

int play(game *mygame)
{
    bank data;
    void *pointer;
    int size = TILE_SIZE;

    data.mygame = mygame;
    data.xvar = mlx_init();
    data.window = mlx_new_window(data.xvar, mygame->columns * 128, mygame->rows * 128, "titolo");
    mlx_key_hook(data.window, key_pressed, &data);

    put_map(&data);

    mlx_loop(data.xvar);
    return (0);
}