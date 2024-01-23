/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:18:23 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/11 17:13:48 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr_s;
	char	*ans;

	ans = NULL;
	ptr_s = (char *)s;
	while (*ptr_s)
	{
		if (*ptr_s == (char)c)
			ans = ptr_s;
		ptr_s++;
	}
	if (c == 0)
		return (ptr_s);
	return (ans);
}
