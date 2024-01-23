/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:38:47 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/08 12:48:07 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_bzero(void *b, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	ptr = (unsigned char *) b;
	i = 0;
	while (i < n)
	{
		*ptr = (unsigned char) 0;
		ptr++;
		i++;
	}
	return (b);
}
