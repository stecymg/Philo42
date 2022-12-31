#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>

# define ERROR -1
# define THINK 0
# define EAT 2
# define SLEEP 3
# define NB_MAX_THREAD 1024
# define DEAD -2
# define ID_STATUS 4

// structure

typedef struct s_time
{
    int     r_start;
    int     r_ustart;
    int     runtime;
}   t_time;

typedef struct s_thread
{
    int     terminate;
    int     died;
    pthread_t   thread[NB_MAX_THREAD];
    pthread_t   death;
    pthread_mutex_t lock;
    pthread_mutex_t state;
    pthread_mutex_t *fork;
    pthread_mutex_t runtime;
}   t_thread;

typedef struct  s_time_to
{
    int     die;
    int     sleep;
    int     eat;
    int     nbr_eat;
}   t_time_to;

typedef struct  s_state
{
    int *id;
}   t_state;

typedef struct s_data
{
    int     id;
    int     id_philo_dead;
    int     launch;
    int     last_eat;
    int     nb_meal;
    int     nb_philo;
    int     left;
    int     right;
    int     death;
    t_time_to   time_to;
    t_time      *time;
    t_thread    *philo;
    t_state     state;
}   t_data;



#endif