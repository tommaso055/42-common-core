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

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && *str)
	{
		str++;
		len++;
	}
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*ans;
	int		space_to_allocate;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	space_to_allocate = ft_strlen(s1) + ft_strlen(s2) + 1;
	ans = (char *)malloc(space_to_allocate * sizeof(char));
	if (ans == NULL)
		return (NULL);
	while (s1[++i])
		ans[i] = s1[i];
	while (s2[++j])
		ans[i + j] = s2[j];
	ans[i + j] = '\0';
	free(s1);
	free(s2);
	return (ans);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;
	size_t	s_len;

	if (!s || len == 0)
		return (NULL);
	i = 0;
	s_len = ft_strlen(s);
	if (s_len < len)
		len = s_len;
	substring = (char *)malloc((len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	while (i < len && start <= s_len)
	{
		substring[i] = s[i + start];
		i++;
	}
	substring[i] = '\0';
	return (substring);
}

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
			if (read(fd, buffer, BUFFER_SIZE) <= 0)
			{
				free(buffer);
				return ;
			}
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
		index++;
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
		return (next_line);
	remaining = ft_substr(next_line, index, ft_strlen(next_line + index));
	return_str = ft_substr(next_line, 0, index);
	free(next_line);
	return (return_str);
}

#include <fcntl.h>
#include <stdio.h>

int main(void)
{
	int fd;
	char *line;

	fd = open("get_next_line.h", O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open file");
		return 1;
	}

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	close(fd);
	return 0;
}
