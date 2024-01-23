/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 14:22:31 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/08 14:26:00 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		length;
	char	*ans;
	int		i;

	if (!s || !f)
		return (NULL);
	length = ft_strlen(s);
	ans = (char *)malloc(length + 1);
	if (ans == NULL)
		return (NULL);
	i = 0;
	while (i < length)
	{
		ans[i] = f(i, s[i]);
		i++;
	}
	ans[i] = '\0';
	return (ans);
}
