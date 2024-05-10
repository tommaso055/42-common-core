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

// size_t	ft_strlen(const char *str)
// {
// 	size_t	len;

// 	len = 0;
// 	while (str && *str != 0)
// 	{
// 		str++;
// 		len++;
// 	}
// 	return (len);
// }

// int		contains(char *str, char c)
// {
// 	int	i;

// 	if (!str)
// 		return (0);
// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i++] == c)
// 			return (1);
// 	}
// 	return (0);
// }

// size_t	ft_strlcpy(char *dst, const char *src, size_t size)
// {
// 	size_t	i;

// 	i = 0;
// 	if (size > 0)
// 	{
// 		while (i < size - 1 && src[i])
// 		{
// 			dst[i] = src[i];
// 			i++;
// 		}
// 		dst[i] = '\0';
// 	}
// 	while (src[i])
// 		i++;
// 	return (i);
// }

// char	*ft_strjoin(char *back, char *buff)
// {
// 	char	*str;
// 	size_t	i;
// 	size_t	j;

// 	if (!back)
// 	{
// 		back = malloc(1 * sizeof(char));
// 		back[0] = '\0';
// 	}
// 	if (!back || !buff)
// 		return (NULL);
// 	str = malloc(sizeof(char) * ((ft_strlen(back) + ft_strlen(buff)) + 1));
// 	if (str == NULL)
// 		return (NULL);
// 	i = -1;
// 	j = 0;
// 	if (back)
// 		while (back[++i] != '\0')
// 			str[i] = back[i];
// 	while (buff[j] != '\0')
// 		str[i++] = buff[j++];
// 	str[ft_strlen(back) + ft_strlen(buff)] = '\0';
// 	free (back);
// 	return (str);
// }

// char	*ft_substr(char *s, unsigned int start, size_t len, int free_s)
// {
// 	char	*substring;
// 	size_t	i;
// 	size_t	s_len;

// 	i = 0;
// 	if (!s || !s[i] || len == 0)
// 	{
// 		if (free_s)
// 			free(s);
// 		return (NULL);
// 	}
// 	substring = (char *)malloc((len + 1) * sizeof(char));
// 	if (substring == NULL)
// 		return (NULL);
// 	while (i < len && start <= ft_strlen(s))
// 	{
// 		substring[i] = s[i + start];
// 		i++;
// 	}
// 	substring[i] = '\0';
// 	if (free_s)
// 		free(s);
// 	return (substring);
// }


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
	static char	*static_memory;
	char		*current_line;
	ssize_t		index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	static_memory = readfile(fd, static_memory);
	if (!static_memory)
		return (NULL);
	index = get_nl_index(static_memory);
	current_line = ft_substr(static_memory, 0, index, 0);
	static_memory = ft_substr(static_memory, index, ft_strlen(static_memory + index), 1);
	// current_line = ft_writing(static_memory);
	// static_memory = ft_new_static(static_memory);
	return(current_line);
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
