#include "philo.h"

void    putnbr_fd(int number, int fd)
{
    char    digit;

    if (number >= 10)
    {
        putnbr_fd(number / 10, fd);
        putnbr_fd(number % 10, fd);
    }
    else
    {
        digit = number + '0';
        write(fd, &digit, 1);
    }
}

void    putstr_fd(char *str, int fd)
{
    if (str == 0)
        return ;
    while (*str)
    {
        write(fd, str++, 1);
    }
}