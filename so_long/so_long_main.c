/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:30:07 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/18 17:30:10 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**init_map(char *file_name, t_game *mg)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(file_name, O_RDONLY);
	mg->map = (char **)malloc(mg->rows * sizeof(char *));
	while (i < mg->rows)
	{
		mg->map[i] = get_next_line(fd);
		if ((int)ft_strlen(mg->map[i]) != (mg->cols + 1))
			if ((int)ft_strlen(mg->map[i]) != (mg->cols) || get_next_line(fd))
				mg->checks++;
		i++;
	}
	close (fd);
	mg->vis = init_zeroes(mg->rows, mg->cols);
	return (mg->map);
}

t_point	*get_info(char *file_name, t_game *mg, int column)
{
	t_point	*entrance;
	int		fd;
	char	*line;

	fd = open (file_name, O_RDONLY);
	line = get_next_line(fd);
	mg->cols = ft_strlen(line) - 1;
	while (line)
	{
		while (line[column] && line[column] != '\n')
		{
			if (line[column] == ENTR && mg->n_entrances++ == 0)
				entrance = ft_lstnew(mg->rows, column);
			if (line[column] == COLL)
				(mg->n_collectibles)++;
			if (line[column++] == EXIT)
				(mg->n_exits)++;
		}
		free(line);
		mg->rows++;
		line = get_next_line(fd);
		column = 0;
	}
	close(fd);
	return (entrance);
}

void	set_up(t_game *mg)
{
	mg->n_collectibles = 0;
	mg->n_entrances = 0;
	mg->rows = 0;
	mg->n_exits = 0;
	mg->checks = 0;
	mg->reachable_collectibles = 0;
	mg->move_counter = 0;
}

int	main(int argc, char **argv)
{
	t_game	mg;
	t_point	*entrance;

	if (argc != 2)
	{
		ft_printf("%s", "solo un argomento, scemo");
		return (0);
	}
	set_up(&mg);
	entrance = get_info(argv[1], &mg, 0);
	init_map(argv[1], &mg);
	if (mg.n_entrances != 1 || mg.n_exits != 1 || mg.checks > 0)
	{
		throw_error(&mg, entrance);
		return (0);
	}
	if (!is_valid(&mg, ft_lstnew(entrance->row, entrance->column)))
	{
		throw_error(&mg, entrance);
		return (0);
	}
	play(&mg, entrance);
	terminate_program(&mg, entrance);
	return (0);
}
