/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
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

int		contains(char *str, char c)
{
	int	i;

	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i++] == c)
			return (1);
	}
	return (0);
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
