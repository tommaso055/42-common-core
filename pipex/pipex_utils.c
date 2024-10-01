#include "pipex.h"

void destroy_matrix(char **matrix)
{
    if (!matrix)
        return;
    for (int i = 0; matrix[i] != NULL; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	**paths;
	char	*path;

	paths = NULL;
	i = 0;
	while (envp[i])
		{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
			{
				paths = ft_split(envp[i] + 5, ':');
				break ;
			}
			i++;
		}
	if (!paths)
		exit(-1);
	i = 0;
	cmd = ft_strjoin("/", cmd);
	path = ft_strjoin(paths[i], cmd);
	while (access(path, X_OK))
	{
		free(path);
		if (!paths[i + 1])
			exit(-1);
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