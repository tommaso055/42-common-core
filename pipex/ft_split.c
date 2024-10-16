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

#include "pipex.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	int		quotes;

	i = 0;
	quotes = 0;
	if (size > 0)
	{
		while (i < size - 1 && src[i])
		{
			if (src[i] == '\'')
			{
				quotes++;
				i++;
				continue ;
			}
			dst[i - quotes] = src[i];
			i++;
		}
		dst[i - quotes] = '\0';
	}
	while (src[i])
		i++;
	return (i);
}

size_t	count_n_words(char const *str, char c, int quotes, size_t i)
{
	size_t	count;
	size_t	valid;

	count = 0;
	valid = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			quotes++;
		if (str[i] == c && !(quotes % 2))
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
	int		quotes;

	len = 1;
	quotes = 0;
	if (s[i] == '\'')
		quotes++;
	while ((s[i + len] != c && s[i + len]) || (quotes % 2))
	{
		if (s[i + len] == '\'')
			quotes++;
		len++;
	}
	*dst = (char *)malloc((len + 1 - quotes) * sizeof(char));
	ft_strlcpy(*dst, s + i, len + 1);
	return (i + len);
}

char	**ft_split(char const *s, char c)
{
	size_t	n_words;
	char	**arr_to_return;
	size_t	i;
	size_t	j;

	if (!s)
		return (NULL);
	n_words = count_n_words(s, c, 0, 0);
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
