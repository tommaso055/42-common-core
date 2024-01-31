#include "get_next_line.h"

char    *ft_strjoin(char const *s1, char const *s2)
{
    int     i;
    int     j;
    char    *ans;
    int     space_to_allocate;

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

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
    char    *substring;
    size_t  i;
    size_t  s_len;

    if (!s || len < 0)
        return (NULL);
    i = 0;
    s_len = ft_strlen(s);
    if (s_len < len)
        len = s_len;
    substring = (char *)malloc((len + 1) * sizeof(char));
    if (substring == NULL)
        return (NULL);
    while (i < len && start <= s_len)
    {
        substring[i] = s[i + start];
        i++;
    }
    substring[i] = '\0';
    return (substring);
}
