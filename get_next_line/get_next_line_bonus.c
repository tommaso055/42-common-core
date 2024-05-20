/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:51:07 by tdonato           #+#    #+#             */
/*   Updated: 2024/04/02 16:51:10 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*readfile(int fd, char *static_memory)
{
	int		bytes;
	char	*buffer;

	bytes = 1;
	while (!contains(static_memory, '\n') && bytes > 0)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (!buffer)
			return (NULL);
		if (bytes > 0)
		{
			buffer[bytes] = 0;
			static_memory = ft_strjoin(static_memory, buffer);
		}
		free(buffer);
	}
	return (static_memory);
}

ssize_t	get_nl_index(char *static_memory)
{
	ssize_t	index;

	index = 0;
	while (static_memory[index] != 0)
	{
		if (static_memory[index++] == '\n')
			return (index);
	}
	return (index);
}

char	*get_next_line(int fd)
{
	static char	*static_mem;
	char		*current_line;
	ssize_t		index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_mem = readfile(fd, static_mem);
	if (!static_mem)
		return (NULL);
	index = get_nl_index(static_mem);
	current_line = ft_substr(static_mem, 0, index, 0);
	static_mem = ft_substr(static_mem, index, ft_strlen(static_mem + index), 1);
	return (current_line);
}
