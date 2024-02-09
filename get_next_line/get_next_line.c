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
		if (temp_str[i] == -1)
			return (NULL);
		while (temp_str[i] != '\0' && keep_itering)
		{
			if(temp_str[i] == '\n')
				keep_itering = 0;
			i++;
		}
		if (keep_itering)
		{
			if (read(fd, buffer, BUFFER_SIZE) == 0)
				return (NULL);
			printf("#\n#\n#\n%s <-(buffer)\n", buffer);
			printf("%s <-(temp_str)\n", temp_str);
			temp_str = ft_strjoin(temp_str, buffer);
			printf("%s <-(all)\n#\n#\n#\n", temp_str);
		}
	}
	printf("%s <-(stringa da printare fino al %d carattere\n#\n#\n)", return_str, (int)i);
	remaining = ft_substr(temp_str, i, sizeof(temp_str) - i);
	return_str = ft_substr(temp_str, 0, i);
	printf("%s <-(stringa printata)\n", return_str);
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
		// printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}
