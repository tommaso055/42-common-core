/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:13:29 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/12 19:13:39 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int	length;
	int	i;

	if (!s || !f)
		return ;
	length = ft_strlen(s);
	i = 0;
	while (i < length)
	{
		f(i, s++);
		i++;
	}
}
