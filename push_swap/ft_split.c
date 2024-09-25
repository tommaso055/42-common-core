/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:38:39 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/25 12:38:43 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	count_n_words(char const *str, char c)
{
	size_t	i;
	size_t	count;
	size_t	valid;

	i = 0;
	count = 0;
	valid = 0;
	while (str[i])
	{
		if (str[i] == c)
		{
			i++;
			if (!valid)
				continue ;
			count++;
			valid = 0;
			continue ;
		}
		i++;
		valid = 1;
	}
	if (valid)
		count++;
	return (count);
}

size_t	next_word(char const *s, size_t i, char c, char **dst)
{
	size_t	len;

	len = 0;
	while (s[i + len] != c && s[i + len])
		len++;
	*dst = (char *)malloc((len + 1) * sizeof(char));
	ft_strlcpy(*dst, s + i, len + 1);
	while (s[i] != c && s[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	size_t	n_words;
	char	**arr_to_return;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	n_words = count_n_words(s, c);
	arr_to_return = (char **)malloc((n_words + 1) * sizeof(char *));
	if (arr_to_return == NULL)
		return (NULL);
	arr_to_return[n_words] = NULL;
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
			i = next_word(s, i, c, arr_to_return + j++);
		else
			i++;
	}
	return (arr_to_return);
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
