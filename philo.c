#include "philo.h"

void	philo_sleep(t_data *data)
{
	if (ft_check_status(data) != DEAD && data->philo->died != DEAD)
	{
		data->state.id[data->id] = SLEEP;
		pthread_mutex_unlock(&data->philo->state);
		print_life(data, "sleeping");
		ft_usleep(data, data->time_to.sleep);
		if (ft_check_status(data) == DEAD || data->philo->died == DEAD)
		{
			pthread_mutex_unlock(&data->philo->state);
			return ;
		}
		else
			pthread_mutex_unlock(&data->philo->state);
		philo_think(data);
	}
	else
		pthread_mutex_unlock(&data->philo->state);
}

void	philo_eat(t_data *data)
{
	if (ft_check_status(data) != DEAD && data->philo->died != DEAD)
	{
		data->state.id[data->id] = EAT;
		pthread_mutex_unlock(&data->philo->state);
		data->nb_meal++;
		print_life(data, "eating");
		data->last_eat = update_runtime(data);
		pthread_mutex_unlock(&data->philo->runtime);
		ft_usleep(data, data->time_to.eat);
		pthread_mutex_unlock(&data->philo->fork[data->right]);
		pthread_mutex_unlock(&data->philo->fork[data->left]);
		if (ft_check_status(data) == DEAD || data->philo->died == DEAD
			|| data->nb_meal == data->time_to.eat)
		{
			pthread_mutex_unlock(&data->philo->state);
			return ;
		}
		pthread_mutex_unlock(&data->philo->state);
		philo_sleep(data);
	}
	else
		ft_unlock_all(data);
}

void	philo_think(t_data *data)
{
	if (ft_check_status(data) != THINK)
	{
		pthread_mutex_unlock(&data->philo->state);
		if (ft_check_status(data) != DEAD && data->philo->died != DEAD)
		{
			data->state.id[data->id] = THINK;
			print_life(data, "thinking");
			pthread_mutex_unlock(&data->philo->state);
		}
		else
		{
			pthread_mutex_unlock(&data->philo->state);
			return ;
		}
	}
	else
		pthread_mutex_unlock(&data->philo->state);
}

void	one_philo(t_data *data)
{
	pthread_mutex_lock(&data->philo->fork[data->right]);
	if (data->philo->died != DEAD)
		print_life(data, "has taken a fork");
	pthread_mutex_unlock(&data->philo->fork[data->right]);
	ft_usleep(data, 100000);
	if (ft_check_status(data) == DEAD || data->philo->died == DEAD)
		pthread_mutex_unlock(&data->philo->state);
	return ;
}

// jappelle un mutex pour le philo qui naura pas dormi et jappelle philo_eat quand je mange
void	take_fork_and_eat(t_data *data)
{
	if (data->id % 2 == 1 && data->launch != 1)
	{
		data->launch = 1;
		ft_usleep2(data, 2);
	}
	if (data->nb_philo == 1)
	{
		one_philo(data);
		return ;
	}
	pthread_mutex_lock(&data->philo->state);
	if (data->philo->died != DEAD)
	{
		pthread_mutex_unlock(&data->philo->state);
		pthread_mutex_lock(&data->philo->fork[data->right]);
		if (data->philo->died != DEAD)
			print_life(data, "has taken a fork");
		pthread_mutex_lock(&data->philo->fork[data->left]);
		if (data->philo->died != DEAD)
			print_life(data, "has taken a fork");
		ft_get_eat(data);
	}
	else
		pthread_mutex_unlock(&data->philo->state);
}