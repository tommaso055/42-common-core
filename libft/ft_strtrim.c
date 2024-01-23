/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:18:23 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/11 17:13:48 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	contains(const char *str, const char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		str++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		len;
	int		first;
	int		last;
	char	*ans;
	int		i;

	if (!s1 || !set)
		return (NULL);
	i = 0;
	len = ft_strlen(s1);
	first = 0;
	last = len - 1;
	while (contains(set, s1[first]))
		first++;
	while (contains(set, s1[last]) && last > first)
		last--;
	ans = (char *)malloc((last - first + 2) * sizeof(char));
	if (ans == NULL)
		return (NULL);
	while (first <= last)
		ans[i++] = s1[first++];
	ans[i] = '\0';
	return (ans);
}
