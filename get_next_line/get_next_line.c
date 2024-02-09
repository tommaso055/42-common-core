#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	static char	*remaining;
	size_t		i;
	char		*temp_str;
	int			keep_itering;
	char		*buffer;
	char		*return_str;

	i = 0;
	keep_itering = 1;
	buffer = malloc(BUFFER_SIZE + 1);
	if (remaining)
	{
		temp_str = malloc(ft_strlen(remaining) + 1);
		if (!temp_str)
			return (NULL);
		ft_strlcpy(temp_str, remaining, BUFFER_SIZE);
		printf("%s (end)\n", temp_str);
	}
	else
	{
		temp_str = malloc(BUFFER_SIZE + 1);
		if (!temp_str)
			return (NULL);
		read(fd, temp_str, BUFFER_SIZE);
	}
	while (keep_itering)
	{
		while (temp_str[i] != '\0' && keep_itering)
		{
			if(temp_str[i] == '\n')
				keep_itering = 0;
			i++;
		}
		if (keep_itering)
		{
			read(fd, buffer, BUFFER_SIZE);
			// if (!buffer)
			// 	return (NULL);
			temp_str = ft_strjoin(temp_str, buffer);
		}
	}
	remaining = ft_substr(temp_str, i, sizeof(temp_str) - i);
	return_str = ft_substr(temp_str, 0, i);
	return (return_str);
}

#include <fcntl.h>
int main()
{
	int fd;
	fd = open("get_next_line.c", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return 1;
	}
	char *line;

	int i = 20;
	while (i--)
	// while ((line = get_next_line(fd)) != NULL)
	{
		line = get_next_line(fd);
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}
