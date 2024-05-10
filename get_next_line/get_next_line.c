/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
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
	while (!contains(static_memory, '\n'), bytes > 0)
	{
		buffer = malloc(BUFFER_SIZE + 1);
		bytes = read(fd, buffer, BUFFER_SIZE);
		buffer[bytes] = 0;
		static_memory = ft_strjoin(static_memory, buffer);
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
		if (static_memory[index++] == 0)
			return (index);
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*static_memory;
	char		*current_line;
	ssize_t		index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_memory = readfile(fd, static_memory);
	if (!static_memory)
		return (NULL);
	if (!contains(static_memory, '\n'))
	{
		current_line = malloc(ft_strlen(static_memory) + 1);
		ft_strlcpy(current_line, static_memory, ft_strlen(static_memory) + 1);
		free(static_memory);
		return (current_line);
	}
	index = get_nl_index(static_memory);
	current_line = ft_substr(static_memory, 0, index);
	static_memory = ft_substr(static_memory, index, ft_strlen(static_memory + index));
	return(current_line);
}

// #include <fcntl.h>
// #include <stdio.h>

// int main() {
// 	int fd = open("gnlTester-master/files/nl", O_RDONLY);
// 	char *c = get_next_line(fd);
// 	while(c != NULL)
// 	{
// 		printf("%s", c);
// 		free(c);
// 		c = get_next_line(fd);
// 	}
// 	free(c);
// 	return 0;
// }
