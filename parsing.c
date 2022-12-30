#include "philo.h"

static int  string_to_int(char *str)
{
    int n;

    if (str == 0)
        return (-1);
    n = 0;
    while (*str)
    {
        n = (*str - '0') + 10 * n;
        str++;
    }
    return (n);
}

//remplir un tableau avec les arguments
static void fill_tab(char **args,)


//checker si jai que des digits
static int  check_digit(char **args)
{
    int i;

    while (*args)
    {
        i = 0;
        while ((*args)[i] >= '0' && (*args)[i] <= '9')
            i++;
        if ((*args)[i] != 0)
        {
            print_error("Error : Not all arguments are digits\n");
            return (1);
        }
        args++;
    }
    return (0);
}

//parsing : checker le nbre dargs
//si ce sont des nbrs
//mettre string en integer
int parsing(int argc, char **argv, int infos[5])
{
    if (argc < 5 || argc > 6)
    {
        print_error("Error : Bad number of arguments\n");
        return (1);
    }
    argv++;
    if (check_digit(argv))
        return (1);
    fill_tab(argv, infos);
    return (0);
}