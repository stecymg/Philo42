/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 14:41:57 by smontgen          #+#    #+#             */
/*   Updated: 2023/01/22 14:55:34 by smontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//checker si jai que des digits
int	check_digit(int ac, char **av)
{
	int		i;
	char	c;

	while (--ac)
	{
		i = -1;
		while (av[ac][++i])
		{
			c = av[ac][i];
			if (c < '0' || c > '9')
			{
				print_error("Error : Not all arguments are digits\n");
				return (1);
			}
		}
	}
	return (0);
}

//parsing : checker le nbre dargs
//si ce sont des nbrs
//mettre string en integer
int	parsing(int argc, char **argv)
{
	long long	ret;

	if (argc < 5 || argc > 6)
	{
		print_error("Error : Bad number of arguments\n");
		return (1);
	}
	argv++;
	if (check_digit(argc, argv) == ERROR)
		return (ERROR);
	argc -= 1;
	while (--argc > 0)
	{
		ret = ft_atoi(argv[argc]);
		if (ret > 2147483647 || ret < 1)
			return (ERROR);
	}
	return (0);
}
