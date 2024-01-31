#include "get_next_line.h"

char    *get_next_line(int fd)
{
    static char *remaining;
    size_t      i;
    char        *temp_str;
    int         keep_itering;
    char        *c;
    char        *return_str;

    keep_itering = 1;
    remaining = NULL;
    if (remaining)
        temp_str = remaining;
    else
        read(fd, temp_str, BUFF_SIZE);
    while (keep_itering)
    {
        while (temp_str[i] != '\0' && keep_itering)
        {
            if(temp_str[i] == '\n')
                keep_itering = 0;
            i++;
        }
        if (keep_itering)
        {
            read(fd, c, BUFF_SIZE);
            temp_str = strjoin(temp_str, c);
        }
    }
    remaining = ft_substr(temp_str, i, sizeof(temp_str) - i);
    return_str = ft_substr(temp_str, 0, i);
    free(temp_str);
    return (return_str);
}