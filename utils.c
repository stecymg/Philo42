/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:21:49 by smontgen          #+#    #+#             */
/*   Updated: 2023/01/22 15:22:27 by smontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	putstr_fd(char *str, int fd)
{
	if (str == 0)
		return ;
	while (*str)
	{
		write(fd, str++, 1);
	}
}

long long	ft_atoi(const char *str)
{
	long			i;
	int				signe;
	long long int	nbr;

	nbr = 0;
	signe = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '+')
			signe = signe * 1;
		if (str[i] == '-')
			signe = signe * (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nbr = nbr * 10 + str[i] - 48;
		i++;
	}
	nbr = nbr * signe;
	return (nbr);
}

int	ft_alloc(t_data	**data, t_state *state, t_thread **philo, int philo_nb)
{
	state->id = (int *)malloc(sizeof(int) * philo_nb);
	if (!state->id)
	{
		free2(*data, state);
		return (ERROR);
	}
	*philo = (t_thread *)malloc(sizeof(t_thread));
	if (!*philo)
	{
		free3(*data, state, *philo);
		return (ERROR);
	}
	(*philo)->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* philo_nb);
	if (!(*philo)->fork)
	{
		free3(*data, state, *philo);
		return (ERROR);
	}
	return (0);
}
