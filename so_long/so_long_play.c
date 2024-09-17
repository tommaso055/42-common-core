#include "so_long.h"

// int key_pressed(int keysim, bank *param)
// {

//     if (keysim == XK_Escape)
//     {
//         mlx_destroy_window(param->xvar, param->window);
//         mlx_destroy_display(param->xvar);
//         free(param->xvar);
//         terminate_program(param->mygame);
//         exit(0);
//     }
//     return (0);
// }

// void put_map(bank *data)
// {
//     int i;
//     int j;
//     void *lava;
//     void *stone;
//     int size = TILE_SIZE;

//     i = 0;
//     j = 0;
//     lava = mlx_xpm_file_to_image(data->xvar, LAVA, &size, &size);
//     stone = mlx_xpm_file_to_image(data->xvar, STONE, &size, &size);
// 	while(i < data->mygame->rows)
// 	{
// 		while (j < data->mygame->columns)
// 		{
// 			if (data->mygame->map[i][j] == WALL)
//                 mlx_put_image_to_window(data->xvar, data->window, lava, j * 128, i * 128);
//             else
//                 mlx_put_image_to_window(data->xvar, data->window, stone, j * 128, i * 128);
// 			j++;
// 		}
// 		i++;
// 		j = 0;
// 	}
// }

// int play(game *mygame)
// {
//     bank data;
//     void *pointer;
//     int size = TILE_SIZE;

//     data.mygame = mygame;
//     data.xvar = mlx_init();
//     data.window = mlx_new_window(data.xvar, mygame->columns * 128, mygame->rows * 128, "titolo");
//     mlx_key_hook(data.window, key_pressed, &data);

//     put_map(&data);

//     mlx_loop(data.xvar);
//     return (0);
// }

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
                mlx_put_image_to_window(data->xvar, data->window, grass, j * 128, i * 128);
            if (data->mygame->map[i][j] == ENTRANCE)
                mlx_put_image_to_window(data->xvar, data->window, player, j * 128, i * 128);
            if (data->mygame->map[i][j] == COLLECTIBLE)
                mlx_put_image_to_window(data->xvar, data->window, book, j * 128, i * 128);
            if (data->mygame->map[i][j] == EXIT)
                mlx_put_image_to_window(data->xvar, data->window, vortex, j * 128, i * 128);
            if (data->mygame->map[i][j] == EMPTY)
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