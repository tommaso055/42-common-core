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

char	*initialize_from(int fd, char *remaining)
{
	int		space_to_allocate;
	char	*return_str;

	space_to_allocate = BUFFER_SIZE + 1;
	if (ft_strlen(remaining))
		space_to_allocate = ft_strlen(remaining) + 1;

	return_str = malloc(space_to_allocate);
	if (!return_str)
		return (NULL);

	if (ft_strlen(remaining))
		ft_strlcpy(return_str, remaining, ft_strlen(remaining) + 1);
	else
	{
		if (read(fd, return_str, BUFFER_SIZE) <= 0)
			{
				free(return_str);
				return_str = NULL;
			}
	}
	return (return_str);
}

void	until_nl(int fd, char **next_line)
{
	size_t		i;
	int			keep_itering;
	char		*buffer;
	int			bytes;

	i = 0;
	keep_itering = 1;
	while (keep_itering)
	{
		while (next_line[0][i] != 0 && keep_itering)
			if (next_line[0][i++] == '\n')
				keep_itering = 0;
		if (keep_itering)
		{
			buffer = malloc(BUFFER_SIZE + 1);
			bytes = read(fd, buffer, BUFFER_SIZE);
			if (bytes <= 0)
			{
				free(buffer);
				return ;
			}
			buffer[bytes] = '\0';
			*next_line = ft_strjoin(*next_line, buffer);
		}
	}
}

ssize_t	get_nl_index(char *next_line)
{
	ssize_t	index;

	index = 0;
	while(next_line[index] != 0)
	{
		if (next_line[index++] == '\n')
			return (index);
	}
	return (-1);
}

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*next_line;
	ssize_t		index;
	char		*return_str;

	next_line = initialize_from(fd, (char *)remaining);
	free(remaining);
	if (!next_line)
		return (NULL);
	
	until_nl(fd, &next_line);
	index = get_nl_index(next_line);
	if (index == -1)
	{
		remaining = NULL;
		return (next_line);
	}
	remaining = ft_substr(next_line, index, ft_strlen(next_line + index));
	return_str = ft_substr(next_line, 0, index);
	free(next_line);
	return (return_str);
}

// #include <fcntl.h>
// #include <stdio.h>

// int main() {
// 	int fd = open("get_next_line.h", O_RDONLY);
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