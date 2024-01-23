/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 16:29:19 by tdonato           #+#    #+#             */
/*   Updated: 2024/01/11 16:40:00 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_fill(char *ans, int n, int i)
{
	int	min_i;

	min_i = 0;
	if (n < 0)
	{
		ans[0] = '-';
		n *= -1;
		min_i++;
	}
	while (i >= min_i)
	{
		ans[i--] = (char)(n % 10 + 48);
		n = n / 10;
	}
}

int	ft_len(int n)
{
	int	len;

	len = 1;
	if (n < 0)
	{
		n *= -1;
		len++;
	}
	while (n >= 10)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*ans;

	if (n == -2147483648)
	{
		ans = (char *)malloc(12);
		if (ans == NULL)
			return (NULL);
		ft_strlcpy(ans, "-2147483648", 12);
		return (ans);
	}
	len = ft_len(n);
	ans = (char *)malloc(len + 1);
	if (ans == NULL)
		return (NULL);
	ft_fill(ans, n, len - 1);
	ans[len] = '\0';
	return (ans);
}
