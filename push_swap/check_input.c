#include "push_swap.h"

void    check_input(int argc, char **argv)
{
    int i;
    int j;

    i = 1;
    while (i < argc)
    {
        j = -1;
        while (argv[i][++j])
            if (argv[i][j] < '0' || argv[i][j] > '9' && (j != 0
                || (argv[i][j] != '-' || argv[i][j] != '+')))
                terminate(NULL, NULL, "Error\nInvalid input");
        if ((argv[i][0] == '-' || argv[i][0] == '+') && ft_strlen(argv[i]) > 11)
        if (argv[i][0] = '-' && ft_strlen(argv[i]) > 11)
        i++;
    }
}