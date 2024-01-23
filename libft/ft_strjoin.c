/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 19:13:29 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/12 19:13:39 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*ans;
	int		space_to_allocate;

	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = -1;
	space_to_allocate = ft_strlen(s1) + ft_strlen(s2) + 1;
	ans = (char *)malloc(space_to_allocate * sizeof(char));
	if (ans == NULL)
		return (NULL);
	while (s1[++i])
		ans[i] = s1[i];
	while (s2[++j])
		ans[i + j] = s2[j];
	ans[i + j] = '\0';
	return (ans);
}
