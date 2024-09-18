/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_play_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:30:07 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/18 17:30:10 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	set_up_sprites(t_bank *data, t_sprites *info, int size)
{
	info->grass = mlx_xpm_file_to_image(data->xvar, GRASS, &size, &size);
	info->stone = mlx_xpm_file_to_image(data->xvar, STONE, &size, &size);
	info->book = mlx_xpm_file_to_image(data->xvar, BOOK, &size, &size);
	info->vortex = mlx_xpm_file_to_image(data->xvar, VORTEX, &size, &size);
	info->player = mlx_xpm_file_to_image(data->xvar, PLAYER, &size, &size);
	info->p_e = mlx_xpm_file_to_image(data->xvar, PLAYER_EXIT, &size, &size);
}

void	destroy_sprites(t_bank *data)
{
	mlx_destroy_image(data->xvar, data->info.grass);
	mlx_destroy_image(data->xvar, data->info.stone);
	mlx_destroy_image(data->xvar, data->info.book);
	mlx_destroy_image(data->xvar, data->info.vortex);
	mlx_destroy_image(data->xvar, data->info.player);
	mlx_destroy_image(data->xvar, data->info.p_e);
}

void	put_map(t_bank *data, t_sprites *info, int i, int j)
{
	int	s;

	s = TILE_SIZE;
	while (i < data->mg->rows)
	{
		while (j < data->mg->cols)
		{
			if (data->mg->map[i][j] == WALL)
				PUT_IMG(data->xvar, data->window, info->stone, j * s, i * s);
			if (data->mg->map[i][j] == ENTR)
				PUT_IMG(data->xvar, data->window, info->player, j * s, i * s);
			if (data->mg->map[i][j] == COLL)
				PUT_IMG(data->xvar, data->window, info->book, j * s, i * s);
			if (data->mg->map[i][j] == EXIT)
				PUT_IMG(data->xvar, data->window, info->vortex, j * s, i * s);
			if (data->mg->map[i][j] == EMPTY)
				PUT_IMG(data->xvar, data->window, info->grass, j * s, i * s);
			if (data->mg->map[i][j] == 'F')
				PUT_IMG(data->xvar, data->window, info->p_e, j * s, i * s);
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
	if (data->mg->map[data->p->row + dc][data->p->column + dr] != WALL)
	{
		if (data->mg->map[data->p->row][data->p->column] == 'F')
			data->mg->map[data->p->row][data->p->column] = EXIT;
		else
			data->mg->map[data->p->row][data->p->column] = EMPTY;
		if (data->mg->map[data->p->row + dc][data->p->column + dr] == COLL)
			data->mg->reachable_coll--;
		if (data->mg->map[data->p->row + dc][data->p->column + dr] == EXIT)
		{
			if (!data->mg->reachable_coll)
			{
				ft_printf("%s", "YOU WON!");
				key_pressed(XK_Escape, data);
			}
			data->mg->map[data->p->row + dc][data->p->column + dr] = 'F';
		}
		else
			data->mg->map[data->p->row + dc][data->p->column + dr] = ENTR;
		data->p->row = data->p->row + dc;
		data->p->column = data->p->column + dr;
		data->mg->move_counter++;
		ft_printf("You have moved %d times\n", data->mg->move_counter);
	}
}
