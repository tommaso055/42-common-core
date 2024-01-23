/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:13:29 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/12 19:13:39 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*new_str;
	size_t	i;

	len = ft_strlen(s1);
	new_str = (char *)malloc((len + 1) * sizeof(char));
	if (new_str)
	{
		i = 0;
		while (i++ < len + 1)
			new_str[i - 1] = (char)s1[i - 1];
	}
	return (new_str);
}
