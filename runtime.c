/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:19:29 by smontgen          #+#    #+#             */
/*   Updated: 2023/01/22 15:19:38 by smontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_time(t_data **data)
{
	int		i;
	t_time	*time;

	i = 0;
	time = (t_time *)malloc(sizeof(t_time));
	if (!time)
	{
		free1(*data);
		print_error("Error : Alloc time\n");
		return (ERROR);
	}
	time->r_start = get_time(2);
	time->r_ustart = get_time(0);
	time->runtime = 0;
	while (i < (*data)->philo_nb)
	{
		(*data)[i].time = time;
		i++;
	}
	return (0);
}

long	get_time(int flag)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	if (flag == 1)
		printf("[%ld] ", current.tv_usec);
	if (flag == 2)
		return (current.tv_sec);
	return (current.tv_usec);
}

long	new_runtime(t_data *data)
{
	pthread_mutex_lock(&data->philo->runtime);
	data->time->runtime = (get_time(2) - data->time->r_start) * 1000
		+ ((get_time(0)) - (data->time->r_ustart)) / 1000;
	return (data->time->runtime);
}

void	print_time(t_data *data)
{
	new_runtime(data);
	printf("%d", data->time->runtime);
}
