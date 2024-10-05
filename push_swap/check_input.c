/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 17:58:33 by tdonato           #+#    #+#             */
/*   Updated: 2024/09/27 17:58:35 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	check_input(int argc, char **argv, int i)
{
	int		j;
	int		sign;
	char	*str;

	sign = 1;
	while (i < argc)
	{
		str = argv[i];
		j = -1;
		if (argv[i][0] == '-' || argv[i][0] == '+')
			str++;
		if (argv[i][0] == '+' || argv[i][0] == '-')
			j++;
		if (argv[i][0] == '-')
			sign = -1;
		while (argv[i][++j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
		}
		if (handle_check(str, sign))
			return (1);
		i++;
	}
	return (0);
}

int	handle_check(char *str, int sign)
{
	if (ft_strlen(str) > 10)
		return (1);
	if (ft_strlen(str) == 10 && sign == -1 && ft_strncmp(str, "2147483648"))
		return (1);
	if (ft_strlen(str) == 10 && sign == 1 && ft_strncmp(str, "2147483647"))
		return (1);
	return (0);
}

int	ft_strlen(char *s)
{
	int	l;

	l = 0;
	if (!s)
		return (0);
	while (s[l])
		l++;
	return (l);
}

int	ft_strncmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if (s1[i] > s2[i])
		return (1);
	return (0);
}

void	further_init_stack(int argc, char **argv, t_push_swap *info)
{
	char	**split;
	int		i;

	i = 0;
	if (argc == 2)
	{
		split = ft_split(argv[1], ' ');
		if (check_input(ft_matrixlen(split), split, 0))
		{
			while (split[i])
				free(split[i++]);
			free(split);
			terminate(NULL, NULL, "Error\n");
		}
		info->stack_a = init_stack(ft_matrixlen(split), split, 0);
		while (split[i])
			free(split[i++]);
		free(split);
	}
	else
	{
		if (check_input(argc, argv, 1))
			terminate(NULL, NULL, "Error\n");
		info->stack_a = init_stack(argc, argv, 1);
	}
}
