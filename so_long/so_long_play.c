/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_play.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:30:07 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/18 17:30:10 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_pressed(int keysim, t_bank *data)
{
	int	dx;
	int	dy;

	dx = 0;
	dy = 0;
	if (keysim == XK_w || keysim == XK_a || keysim == XK_s || keysim == XK_d)
	{
		convert_to_move(keysim, &dx, &dy);
		move(dx, dy, data);
		put_map(data, &(data->info), 0, 0);
	}
	if (keysim == XK_Escape)
	{
		destroy_sprites(data);
		mlx_destroy_window(data->xvar, data->window);
		mlx_destroy_display(data->xvar);
		free(data->xvar);
		terminate_program(data->mg, data->p);
		exit(0);
	}
	return (0);
}

int	handle_close(t_bank *data)
{
	key_pressed(XK_Escape, data);
	return (0);
}

int	play(t_game *mg, t_point *entrance)
{
	t_bank	data;
	int		s;

	s = TILE_SIZE;
	data.p = entrance;
	data.mg = mg;
	data.xvar = mlx_init();
	data.window = mlx_new_window(data.xvar, mg->cols * s, mg->rows * s, "game");
	set_up_sprites(&data, &(data.info), TILE_SIZE);
	mlx_key_hook(data.window, key_pressed, &data);
	mlx_hook(data.window, 17, 0, handle_close, &data);
	put_map(&data, &(data.info), 0, 0);
	mlx_loop(data.xvar);
	return (0);
}
