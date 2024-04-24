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
	while (*str)
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


int	init_temp(int fd, char **remaining, char **temp_str)
{
	if (remaining && *remaining && **remaining != 0)
	{
		*temp_str = malloc(ft_strlen(*remaining) + 1);
		if (!(*temp_str))
			return (-1);
		ft_strlcpy(*temp_str, *remaining, ft_strlen(*remaining) + 1);
		free(*remaining);
		return (1);
	}
	else
	{
		*temp_str = malloc(BUFFER_SIZE + 1);
		if (!(*temp_str))
			return (-1);
		if (read(fd, *temp_str, BUFFER_SIZE) <= 0)
			return (-1);
		return (1);
	}
}

ssize_t	set_temp(int fd, char **remaining, char **temp_str, size_t i)
{
	int			keep_itering;
	char		*buffer;

	keep_itering = 1;
	if (init_temp(fd, remaining, temp_str) < 0)
		return (-1);
	while (keep_itering)
	{
		while (temp_str[0][i] != 0 && keep_itering)
			if (temp_str[0][i++] == '\n')
				keep_itering = 0;
		if (keep_itering)
		{
			buffer = malloc(BUFFER_SIZE + 1);
			if (read(fd, buffer, BUFFER_SIZE) <= 0)
			{
				free(buffer);
				return (-2);
			}
			*temp_str = ft_strjoin(*temp_str, buffer);
		}
	}
	return (i);
}

char	*get_next_line(int fd)
{
	static char	*remaining;
	char		*temp_str;
	char		*return_str;
	ssize_t		nli;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	nli = set_temp(fd, &remaining, &temp_str, 0);
	if (nli < 0)
	{
		if (nli == -2)
			return (temp_str);
		free(temp_str);
		return (NULL);
	}
	remaining = ft_substr(temp_str, nli, ft_strlen(temp_str + nli));
	return_str = ft_substr(temp_str, 0, nli);
	free(temp_str);
	return (return_str);
}

#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("gnlTester-master/files/nl", O_RDONLY);
    if (fd == -1)
    {
        perror("Failed to open file");
        return 1;
    }

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }

    close(fd);
    return 0;
}

