#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	init_temp(int fd, char **remaining, char **temp_str)
{
	if (remaining && *remaining && **remaining != 0)
	{
		*temp_str = (char *)malloc(ft_strlen(*remaining) + 1);
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
			if(temp_str[0][i++] == '\n')
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
		return(NULL);
	nli = set_temp(fd, &remaining, &temp_str, 0);
	if (nli < 0)
	{
		if (nli == -2)
			return(temp_str);
		free(temp_str);
		return (NULL);
	}
	remaining = ft_substr(temp_str, nli, ft_strlen(temp_str + nli));
	return_str = ft_substr(temp_str, 0, nli);
	free(temp_str);
	return (return_str);
}
