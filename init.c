#include "philo.h"

/*initialisation des données des philo
(i + 1) % nb_philo c'est une formule pour que le dernier philo
prenne la fourchette du 1er philo
*/
int	init_philo(t_time_to time_to, t_data *data, int nb_philo)
{
	t_state	state;
	t_thread	*philo;
	int	i;

	i = 0;
	if (ft_alloc(&data, &state, &philo, nb_philo) == 1)
		return (1);
	while (i < nb_philo)
	{
		state.id[i] = ID_STATUS;
		data[i].id = i;
		data[i].nb_meal = 0;
		data[i].nb_philo = nb_philo;
		data[i].right = i;
		data[i].left = (i + 1) % nb_philo;
		data[i].last_eat = 0;
		data[i].philo = philo;
		data[i].time_to = time_to;
		data[i].state = state;
		data[i].id_philo_dead = i;
		i++;
	}
}

//innitialisation de toutes les données

int	init_data(t_data **data, int ac, char **av)
{
	t_time_to	time_to;
	int		nb_philo;

	nb_philo = ft_atoi(av[1]);
	time_to.sleep = ft_atoi(av[4]);
	time_to.eat = ft_atoi(av[3]);
	time_to.die = ft_atoi(av[2]);
	time_to.nbr_eat = -1;
	if (ac == 6)
		time_to.nbr_eat = ft_atoi(av[5]);
	*data = (t_data *)malloc(sizeof(t_data) * nb_philo);
	if (!*data)
	{
		ft_free(*data);
		write(2, "ERROR ALLOC\n", 11);
		return (ERROR);
	}
	if (init_philo(time_to, *data, nb_philo) == 1)
		return (ERROR);
	return (0);
}

void	init_mutex(t_data *data)
{
	int	i;

	i = -1;
	data->philo->died = 0;
	data->philo->terminate = 0;
	data->death = 0;
	while (++i < data->nb_philo)
		pthread_mutex_init(&data->philo->fork[i], NULL);
	pthread_mutex_init(&data->philo->lock, NULL);
	pthread_mutex_init(&data->philo->state, NULL);
	pthread_mutex_init(&data->philo->runtime, NULL);
}