/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:19:59 by smontgen          #+#    #+#             */
/*   Updated: 2023/01/22 15:21:26 by smontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(t_data *data, long time_to)
{
	long	start_time;

	start_time = (get_time(2) - data->time->r_start) * 1000
		+ ((get_time(0)) - (data->time->r_ustart)) / 1000;
	while ((new_runtime(data) - start_time) < time_to)
	{
		pthread_mutex_unlock(&data->philo->runtime);
		if (check_status(data) != DEAD && data->philo->died != DEAD)
		{
			pthread_mutex_unlock(&data->philo->state);
			usleep(time_to / (time_to / 2));
		}
		else
		{
			pthread_mutex_unlock(&data->philo->state);
			return ;
		}
	}
	pthread_mutex_unlock(&data->philo->runtime);
}

/*
void	ft_usleep2(t_data *data, long time_to)
{
	long	start_time;

	start_time = (get_time(2) - data->time->r_start) * 1000
		+ ((get_time(0)) - (data->time->r_ustart)) / 1000;
	while ((new_runtime(data) - start_time) < time_to)
	{
		pthread_mutex_unlock(&data->philo->runtime);
		usleep(time_to / (time_to / 2));
	}
	pthread_mutex_unlock(&data->philo->runtime);
}
*/