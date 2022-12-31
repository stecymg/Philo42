#include "philo.h"

void	print_error(char*msg)
{
	if (msg == 0)
		return ;
	putstr_fd(msg, 2);
}