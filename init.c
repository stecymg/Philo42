/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:54:16 by smontgen          #+#    #+#             */
/*   Updated: 2023/01/22 11:56:54 by smontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*initialisation des données pour chaque philo
(i + 1) % philo_nb c'est une formule pour que le dernier philo
prenne la fourchette du 1er philo
*/
int	init_philo(t_time_to time_to, t_data *data, int philo_nb)
{
	t_state		state;
	t_thread	*philo;
	int			i;

	i = 0;
	if (ft_alloc(&data, &state, &philo, philo_nb) == 1)
		return (1);
	while (i < philo_nb)
	{
		state.id[i] = ID_STATUS;
		data[i].id = i;
		data[i].meal_nb = 0;
		data[i].philo_nb = philo_nb;
		data[i].right = i;
		data[i].left = (i + 1) % philo_nb;
		data[i].last_eat = 0;
		data[i].philo = philo;
		data[i].time_to = time_to;
		data[i].state = state;
		data[i].id_philo_dead = i;
		i++;
	}
	return (0);
}

//innitialisation de toutes les données
//philo_eat c'est qd jai largument nbr de repas max 
int	init_data(t_data **data, int ac, char **av)
{
	t_time_to	time_to;
	long		philo_nb;

	philo_nb = ft_atoi(av[1]);
	time_to.sleep = ft_atoi(av[4]);
	time_to.eat = ft_atoi(av[3]);
	time_to.die = ft_atoi(av[2]);
	time_to.philo_eat = -1;
	if (ac == 6)
		time_to.philo_eat = ft_atoi(av[5]);
	*data = (t_data *)malloc(sizeof(t_data) * philo_nb);
	if (!*data)
	{
		free1(*data);
		write(2, "Error Alloc\n", 12);
		return (ERROR);
	}
	if (init_philo(time_to, *data, philo_nb) == 1)
		return (ERROR);
	return (0);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = 0;
	data->philo->died = 0;
	data->philo->end = 0;
	data->death = 0;
	while (i < data->philo_nb)
	{
		pthread_mutex_init(&data->philo->fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->philo->lock, NULL);
	pthread_mutex_init(&data->philo->state, NULL);
	pthread_mutex_init(&data->philo->runtime, NULL);
}
