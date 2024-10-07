/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdonato <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 19:38:11 by tdonato           #+#    #+#             */
/*   Updated: 2024/10/07 19:38:13 by tdonato          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	destroy_matrix(char **matrix)
{
	int	i;

	if (!matrix)
		return ;
	i = 0;
	while (matrix[i] != NULL)
		free(matrix[i++]);
	free(matrix);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path;

	paths = NULL;
	i = -1;
	while (envp[++i] && !paths)
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' &&
			envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
			paths = ft_split(envp[i] + 5, ':');
	}
	i = 0;
	cmd = ft_strjoin("/", cmd);
	path = ft_strjoin(paths[i], cmd);
	while (access(path, X_OK))
	{
		free(path);
		if (!paths[i + 1])
			t("pipex: command not found: ", cmd + 1, cmd, paths);
		path = ft_strjoin(paths[++i], cmd);
	}
	free(cmd);
	destroy_matrix(paths);
	return (path);
}

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
