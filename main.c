/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 11:57:26 by smontgen          #+#    #+#             */
/*   Updated: 2023/01/22 14:53:36 by smontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

//boucle qui varendre une fourchette quand ts les philos nont pas assez manger
//ou ne sont pas mort
void	*routine(void *arg)
{
	t_data	*data;

	data = arg;
	data->launch = 0;
	while (check_status(data) != DEAD && data->philo->died != DEAD
		&& data->meal_nb != data->time_to.philo_eat)
	{
		pthread_mutex_unlock(&data->philo->state);
		take_fork_and_eat(data);
	}
	if ((data->meal_nb != data->time_to.philo_eat || data->philo->died == DEAD)
		&& data->philo->end == 0)
		print_death(data, "died", data->id_philo_dead);
	else if (data->philo->died != DEAD)
		print_life(data, "Max meal nb reached");
	data->philo->end++;
	pthread_mutex_unlock(&data->philo->state);
	return (NULL);
}

//creation des threads avec les paires en 1er puis les impaires un peu apres 
void	create_thread(t_data *data, int philo_nb)
{
	int	i;

	i = 0;
	while (i < philo_nb)
	{
		if (pthread_create(&data->philo->thread[i], NULL,
				routine, &data[i]) == -1)
			print_error("Error : thread not create\n");
		i++;
		i++;
	}
	i = 1;
	usleep(800);
	while (i < philo_nb)
	{
		if (pthread_create(&data->philo->thread[i], NULL,
				routine, &data[i]) == -1)
			print_error("Error : thread not create\n");
		i++;
		i++;
	}
}

//initiation de tous les process et je check si jai aucun philo mort
int	init_process(int ac, char **av)
{
	t_data	*data;
	int		i;

	i = 0;
	data = NULL;
	if (init_data(&data, ac, av) == ERROR)
		return (ERROR);
	if (init_time(&data) == ERROR)
		return (ERROR);
	init_mutex(data);
	create_thread(data, ft_atoi(av[1]));
	pthread_create(&data->philo->death, NULL, check_death, data);
	while (i < ft_atoi(av[1]))
	{
		pthread_join(data->philo->thread[i], NULL);
		i++;
	}
	pthread_join(data->philo->death, NULL);
	destroy_mutex(data);
	free1(data);
	return (0);
}

int	main(int ac, char **av)
{
	if ((parsing(ac, av) == ERROR) || (ac < 5 || ac > 6))
	{
		printf("Error of args\n");
		return (ERROR);
	}
	return (init_process(ac, av));
}
