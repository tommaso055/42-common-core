/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 15:30:14 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/11 15:44:48 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dst_len;
	size_t	src_len;

	i = 0;
	j = 0;
	src_len = ft_strlen(src);
	if (!dst && !dstsize)
		return (src_len);
	dst_len = ft_strlen(dst);
	if (!dstsize)
		return (src_len);
	if (dstsize < dst_len)
		return (dstsize + src_len);
	while (i < dstsize && dst[i])
		i++;
	while (i + 1 < dstsize && src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (src_len + dst_len);
}
