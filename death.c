/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:45:58 by smontgen          #+#    #+#             */
/*   Updated: 2023/01/22 11:52:58 by smontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_end2(t_data *data)
{
	pthread_mutex_lock(&data->philo->state);
	return (data->philo->end);
}

int	check_end(t_data *data)
{
	if (check_end2(data) == data->philo_nb)
	{
		pthread_mutex_unlock(&data->philo->state);
		return (1);
	}
	else
		pthread_mutex_unlock(&data->philo->state);
	return (0);
}

int	one_philo_died(t_data *data, int counter, int i)
{
	i = 0;
	while (i < counter)
	{
		if ((new_runtime(data - data[i].last_eat > data->time_to.die)
				&& data->state.id[i] != DEAD))
		{
			pthread_mutex_unlock(&data->philo->runtime);
			pthread_mutex_lock(&data->philo->state);
			data->state.id[i] = DEAD;
			data->id_philo_dead = data->id + 1;
			data->philo->died = DEAD;
			pthread_mutex_unlock(&data->philo->state);
			data->death++;
			if (data->death == data->philo_nb)
				return (1);
		}
		else
		{
			pthread_mutex_unlock(&data->philo->runtime);
			i++;
		}
		if (check_end(data) == 1)
			return (1);
	}
	return (0);
}

void	*check_death(void *arg)
{
	t_data	*data;
	int		i;
	int		counter;

	i = 0;
	data = arg;
	counter = data->philo_nb;
	while (1)
	{
		if (one_philo_died(data, counter, i) == 1)
			return (NULL);
	}
	return (NULL);
}
