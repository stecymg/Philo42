/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smontgen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 15:06:58 by smontgen          #+#    #+#             */
/*   Updated: 2023/01/22 17:10:41 by smontgen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <sys/time.h>

# define ERROR -1
# define THINK 0
# define EAT 2
# define SLEEP 3
# define NB_MAX_THREAD 1024
# define DEAD -2
# define ID_STATUS 4

/*structure*/

typedef struct s_time
{
	int	r_start;
	int	r_ustart;
	int	runtime;
}	t_time;

typedef struct s_thread
{
	int				end;
	int				died;
	pthread_t		thread[NB_MAX_THREAD];
	pthread_t		death;
	pthread_mutex_t	lock;
	pthread_mutex_t	state;
	pthread_mutex_t	*fork;
	pthread_mutex_t	runtime;
}	t_thread;

typedef struct s_time_to
{
	int	die;
	int	sleep;
	int	eat;
	int	philo_eat;
}	t_time_to;

typedef struct s_state
{
	int	*id;
}	t_state;

typedef struct s_data
{
	int			id;
	int			id_philo_dead;
	int			launch;
	int			last_eat;
	int			meal_nb;
	int			philo_nb;
	int			left;
	int			right;
	int			death;
	t_time_to	time_to;
	t_time		*time;
	t_thread	*philo;
	t_state		state;
}	t_data;

/*utils.c*/
void		putstr_fd(char *str, int fd);
long long	ft_atoi(const char *str);
long		get_time(int flag);
void		destroy_mutex(t_data *data);
int			ft_alloc(t_data	**data, t_state *state, t_thread **philo,
				int nb_philo);

/*parsing.c*/
int			check_digit(int ac, char **av);
int			parsing(int argc, char **argv);

/*init.c*/
int			init_philo(t_time_to time_to, t_data *data, int philo_nb);
int			init_data(t_data **data, int ac, char **av);
void		init_mutex(t_data *data);

/*philo.c*/
void		philo_sleep(t_data *data);
void		philo_eat(t_data *data);
void		philo_think(t_data *data);
void		one_philo(t_data *data);
void		take_fork_and_eat(t_data *data);

/*print_status.c*/
void		print_life(t_data *data, char *str);
void		print_death(t_data *data, char *str, int id);
int			check_status(t_data *data);

/*main.c*/
void		*routine(void *arg);
void		create_thread(t_data *data, int philo_nb);
int			init_process(int ac, char **av);

/*runtime.c*/
int			init_time(t_data **data);
long		new_runtime(t_data *data);
void		print_time(t_data *data);

/*death.c*/
int			check_end2(t_data *data);
int			check_end(t_data *data);
int			one_philo_died(t_data *data, int counter, int i);
void		*check_death(void *arg);

/*error_msg.c*/
void		print_error(char*msg);

/*usleep.c*/
void		ft_usleep(t_data *data, long time_to);
//void		ft_usleep2(t_data *data, long time_to);

/*free_all.c*/
void		free1(t_data *data);
void		free2(t_data *data, t_state *state);
void		free3(t_data *data, t_state *state, t_thread *philo);
void		unlock_all(t_data *data);

#endif
