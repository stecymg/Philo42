/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 16:02:29 by smontgen          #+#    #+#             */
/*   Updated: 2023/01/22 16:04:32 by smontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free1(t_data *data)
{
	if (data)
	{
		if (data->state.id)
			free(data->state.id);
		if (data->time)
			free(data->time);
		if (data->philo->fork)
			free(data->philo->fork);
		if (data->philo)
			free(data->philo);
		free(data);
	}
}

void	free2(t_data *data, t_state *state)
{
	if (state)
	{
		if (state->id)
			free(state->id);
		free(state);
	}
	free1(data);
	write(2, "Faillure allocation\n", 21);
}

void	free3(t_data *data, t_state *state, t_thread *philo)
{
	if (philo)
		free(philo);
	free2(data, state);
}

void	unlock_all(t_data *data)
{
	pthread_mutex_unlock(&data->philo->state);
	pthread_mutex_unlock(&data->philo->fork[data->id]);
	pthread_mutex_unlock(&data->philo->fork[data->left]);
}
