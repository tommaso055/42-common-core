#include "get_next_line.h"

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

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (ans);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	i;
	size_t	s_len;

	if (!s || len < 0)
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

char	*get_next_line(int fd)
{
	static char	*remaining;
	size_t		i;
	char		*temp_str;
	int			keep_itering;
	char		*c;
	char		*return_str;

	i = 0;
	c = (char *)malloc((BUFF_SIZE + 1) * sizeof(char));
	if (!c)
		return (NULL);
	keep_itering = 1;
	remaining = NULL;
	if (remaining)
	{
		temp_str = (char *)malloc((BUFF_SIZE + 1) * sizeof(char));
		if (!temp_str)
			return (NULL);
		temp_str = remaining;
	}
	else
		read(fd, temp_str, BUFF_SIZE);
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
			read(fd, c, BUFF_SIZE);
			if (!c)
				return (NULL);
			temp_str = ft_strjoin(temp_str, c);
		}
	}
	remaining = ft_substr(temp_str, i, sizeof(temp_str) - i);
	return_str = ft_substr(temp_str, 0, i);
	// free(temp_str);
	return (return_str);
}

#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd; // Assuming you have a file descriptor to test with

	// Open the file or use another method to obtain the file descriptor
	fd = open("get_next_line.c", O_RDONLY);

	if (fd == -1)
	{
		perror("Error opening file");
		return 1;
	}

	char *line;

	// Call get_next_line in a loop until the end of the file is reached
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}

	close(fd);

	return 0;
}