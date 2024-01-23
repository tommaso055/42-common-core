/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 16:21:22 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/08 17:05:46 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr_dst;
	unsigned char	*ptr_src;

	if (!dst && !src)
		return (dst);
	ptr_dst = (unsigned char *) dst;
	ptr_src = (unsigned char *) src;
	if (ptr_dst < ptr_src || ptr_dst >= ptr_src + n)
	{
		while (0 < n--)
			*ptr_dst++ = *ptr_src++;
	}
	else
	{
		ptr_dst = ptr_dst + n - 1;
		ptr_src = ptr_src + n -1;
		while (0 < n--)
			*ptr_dst-- = *ptr_src--;
	}
	return (dst);
}
