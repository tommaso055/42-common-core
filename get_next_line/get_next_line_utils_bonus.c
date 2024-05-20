/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:51:33 by tdonato           #+#    #+#             */
/*   Updated: 2024/04/02 16:51:37 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str && *str != 0)
	{
		str++;
		len++;
	}
	return (len);
}

int	contains(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i++] == c)
			return (1);
	}
	return (0);
}

char	*ft_strjoin(char *back, char *buff)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (!back)
	{
		back = malloc(1 * sizeof(char));
		back[0] = '\0';
	}
	if (!back || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(back) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (back)
		while (back[++i] != '\0')
			str[i] = back[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(back) + ft_strlen(buff)] = '\0';
	free (back);
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len, int free_s)
{
	char	*substring;
	size_t	i;

	i = 0;
	if (!s || !s[i] || len == 0)
	{
		if (free_s)
			free(s);
		return (NULL);
	}
	substring = (char *)malloc((len + 1) * sizeof(char));
	if (substring == NULL)
		return (NULL);
	while (i < len && start <= ft_strlen(s))
	{
		substring[i] = s[i + start];
		i++;
	}
	substring[i] = '\0';
	if (free_s)
		free(s);
	return (substring);
}
