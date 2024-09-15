#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include <X11/keysym.h>
#include <stdlib.h> 

typedef struct bank {
    void *xvar;
    void *window;
} bank;

int key_pressed(int keysim, bank *param)
{

    if (keysim == XK_Escape)
    {
        mlx_destroy_window(param->xvar, param->window);
        exit(0);
    }
    return (0);
}

int main()
{
    bank data;

    data.xvar = mlx_init();
    data.window = mlx_new_window(data.xvar, 1920, 1080, "titolo");
    mlx_key_hook(data.window, key_pressed, &data);
    mlx_loop(data.xvar);
    return (0);
}