#include "push_swap.h"

void    check_input(int argc, char **argv, int start)
{
    int i;
    int j;
    int sign;
    char *str;

    i = start;
    sign = 1;
    while (i < argc)
    {
        str = argv[i];
        j = 0;
        if (argv[i][0] == '+')
        {
            j++;
            str++;
        }
        if (argv[i][0] == '-')
        {
            j++;
            sign = -1;
            str++;
        }
        while (argv[i][j])
            {
                if (argv[i][j] < '0' || argv[i][j] > '9')
                    terminate(NULL, NULL, "Error\nInvalid input");
                    j++;
            }
        if (ft_strlen(str) > 10)
            terminate(NULL, NULL, "Error\nInvalid input");
        if (ft_strlen(str) == 10 && sign == -1 && ft_strncmp(str, "2147483648"))
            terminate(NULL, NULL, "Error\nInvalid input");
        if (ft_strlen(str) == 10 && sign == 1 && ft_strncmp(str, "2147483647"))
            terminate(NULL, NULL, "Error\nInvalid input");
		i++;
    }
}

int ft_strlen(char *s)
{
	int l;

	l = 0;
	if (!s)
		return (0);
	while(s[l])
		l++;
	return (l);
}

int ft_strncmp(char *s1, char *s2)
{
    int i;

	i = 0;
    while(s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    if (s1[i] > s2[i])
        return (1);
    return (0);
}
