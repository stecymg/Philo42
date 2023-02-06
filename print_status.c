/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:33:02 by smontgen          #+#    #+#             */
/*   Updated: 2023/01/30 13:33:09 by smontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_life(t_data *data, char *str)
{
	pthread_mutex_lock(&data->philo->lock);
	print_time(data);
	pthread_mutex_unlock(&data->philo->runtime);
	printf(" %d %s\n", data->id + 1, str);
	pthread_mutex_unlock(&data->philo->lock);
}

void	print_death(t_data *data, char *str, int id)
{
	pthread_mutex_lock(&data->philo->lock);
	print_time(data);
	pthread_mutex_unlock(&data->philo->runtime);
	printf(" %d %s\n", id, str);
	pthread_mutex_unlock(&data->philo->lock);
}

int	check_status(t_data *data)
{
	pthread_mutex_lock(&data->philo->state);
	return (data->state.id[data->id]);
}
