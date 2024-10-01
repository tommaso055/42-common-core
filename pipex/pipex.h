#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>

char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
void    destroy_matrix(char **matrix);
char	*find_path(char *cmd, char **envp);
size_t  ft_strlen(const char *str);