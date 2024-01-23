/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:13:29 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/12 19:13:39 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ans;
	size_t	tot_size;

	tot_size = count * size;
	if (count && size && (4294967295U / size <= count))
		return (NULL);
	ans = (void *)malloc(tot_size);
	if (!ans)
		return (NULL);
	if (ans)
		ft_bzero(ans, tot_size);
	return (ans);
}
