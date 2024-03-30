#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

// size_t	ft_strlen(const char *str)
// {
// 	size_t	len;

// 	len = 0;
// 	while (*str)
// 	{
// 		str++;
// 		len++;
// 	}
// 	return (len);
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

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	int		i;
// 	int		j;
// 	char	*ans;
// 	int		space_to_allocate;

// 	if (!s1 || !s2)
// 		return (NULL);
// 	i = -1;
// 	j = -1;
// 	space_to_allocate = ft_strlen(s1) + ft_strlen(s2) + 1;
// 	ans = (char *)malloc(space_to_allocate * sizeof(char));
// 	if (ans == NULL)
// 		return (NULL);
// 	while (s1[++i])
// 		ans[i] = s1[i];
// 	while (s2[++j])
// 		ans[i	 + j] = s2[j];
// 	ans[i + j] = '\0';
// 	free(s1);
// 	free(s2);
// 	return (ans);
// }

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*substring;
// 	size_t	i;
// 	size_t	s_len;

// 	if (!s || len == 0)
// 		return (NULL);
// 	i = 0;
// 	s_len = ft_strlen(s);
// 	if (s_len < len)
// 		len = s_len;
// 	substring = (char *)malloc((len + 1) * sizeof(char));
// 	if (substring == NULL)
// 		return (NULL);
// 	while (i < len && start <= s_len)
// 	{
// 		substring[i] = s[i + start];
// 		i++;
// 	}
// 	substring[i] = '\0';
// 	return (substring);
// }


// char	*get_next_line(int fd)
// {
// 	static char	*remaining;
// 	size_t		i;
// 	char		*temp_str;
// 	int			keep_itering;
// 	char		*buffer;
// 	char		*return_str;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return(NULL);
// 	i = 0;
// 	keep_itering = 1;
// 	if (remaining && *remaining != 0)
// 	{
// 		temp_str = malloc(ft_strlen(remaining) + 1);
// 		if (!temp_str)
// 			return (NULL);
// 		ft_strlcpy(temp_str, remaining, ft_strlen(remaining) + 1);
// 		free(remaining);
// 	}
// 	else
// 	{
// 		temp_str = malloc(BUFFER_SIZE + 1);
// 		if (!temp_str)
// 			return (NULL);
// 		if (read(fd, temp_str, BUFFER_SIZE) <= 0)
// 		{
// 			free(temp_str);
// 			return (NULL);
// 		}
// 	}
// 	while (keep_itering)
// 	{
// 		while (temp_str[i] != '\0' && keep_itering)
// 		{
// 			if(temp_str[i] == '\n')
// 				keep_itering = 0;
// 			i++;
// 		}
// 		if (keep_itering)
// 		{		
// 			buffer = malloc(BUFFER_SIZE + 1);
// 			if (read(fd, buffer, BUFFER_SIZE) <= 0)
// 			{
// 				free(buffer);
// 				return (temp_str);
// 			}
// 			temp_str = ft_strjoin(temp_str, buffer);
// 		}
// 	}
// 	remaining = ft_substr(temp_str, i, ft_strlen(temp_str + i));
// 	return_str = ft_substr(temp_str, 0, i);
// 	free(temp_str);
// 	return (return_str);
// }


int	init_temp(int fd, char **remaining, char **temp_str)
{
	if (remaining && *remaining && **remaining != 0) // in caso frealo
	{
		*temp_str = (char *)malloc(ft_strlen(*remaining) + 1);
		if (!(*temp_str))
			return (-1);
		ft_strlcpy(*temp_str, *remaining, ft_strlen(*remaining) + 1);
		free(*remaining);
		free(remaining);
		return (1);
	}
	else
	{
		if (remaining && *remaining && **remaining == 0)
		{
			free(*remaining);
			free(remaining);
		}
		*temp_str = malloc(BUFFER_SIZE + 1);
		if (!(*temp_str))
			return (-1);
		if (read(fd, *temp_str, BUFFER_SIZE) <= 0)
			return (-1);
		return (1);
	}
}

ssize_t	set_temp(int fd, char **remaining, char **temp_str)
{
	size_t		i;
	int			keep_itering;
	char		*buffer;

	i = 0;
	keep_itering = 1;
	if (init_temp(fd, remaining, temp_str) < 0)
		return (-1);
	while (keep_itering)
	{
		while (temp_str[0][i] != 0 && keep_itering)
		{
			if(temp_str[0][i] == '\n')
				keep_itering = 0;
			i++;
		}
		if (keep_itering)
		{		
			buffer = malloc(BUFFER_SIZE + 1);
			if (read(fd, buffer, BUFFER_SIZE) <= 0)
			{
				free(buffer);
				return (-1);
			}
			*temp_str = ft_strjoin(*temp_str, buffer);
		}
	}
	return (i);
}

char	*get_next_line(int fd)
{
	static char	**remaining;
	char		**temp_str;
	char		*return_str;
	ssize_t		nli;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return(NULL);
	temp_str = (char **)malloc(sizeof(char *));
	nli = set_temp(fd, remaining, temp_str);
	if (nli < 0)
	{
		return_str = NULL;
		if (*temp_str && **temp_str != 0)
			return_str = *temp_str;
		free(*temp_str);
		free(temp_str);
		return (return_str);
	}
	remaining = (char **)malloc(sizeof(char *));
	*remaining = ft_substr(*temp_str, nli, ft_strlen(*temp_str + nli));
	return_str = ft_substr(*temp_str, 0, nli);
	free(*temp_str);
	free(temp_str);
	return (return_str);
}


// int main() {
// 	int fd = open("get_next_line.h", O_RDONLY);
// 	char *c = get_next_line(fd);
// 	while(c)
// 	{
// 		printf("%s", c);
// 		free(c);
// 		c = get_next_line(fd);
// 	}
// 	free(c);
// 	return 0;
// }
