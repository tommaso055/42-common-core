/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 17:54:40 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/11 18:11:12 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*s1_ptr;
	unsigned char	*s2_ptr;
	size_t			i;

	s1_ptr = (unsigned char *)s1;
	s2_ptr = (unsigned char *)s2;
	i = 0;
	if (!n)
		return (0);
	while (--n && s1_ptr[i] && s2_ptr[i] && s1_ptr[i] == s2_ptr[i])
	{
		i++;
	}
	if (s1_ptr[i] != s2_ptr[i] || (!s1_ptr || !s2_ptr))
		return (s1_ptr[i] - s2_ptr[i]);
	return ('\0');
}
