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

int play(game *mygame)
{
    bank data;

    data.mygame = mygame;
    data.xvar = mlx_init();
    data.window = mlx_new_window(data.xvar, 1920, 1080, "titolo");
    mlx_key_hook(data.window, key_pressed, &data);
    mlx_loop(data.xvar);
    return (0);
}