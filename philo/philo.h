#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>

struct s_prepare
{
	int people;
};

struct s_mutex
{
	pthread_mutex_t *fork;
	pthread_mutex_t print;
};

struct s_philo
{
	pthread_t thread;
	int num_of_philos;
	int time_of_sleep;
	int time_of_eat;
	int time_of_die;
	int must_eat;
	int number;
	int left;
	int right;
	struct s_mutex *mutex;
};

int ft_isdigit(int num);
int av_digitcheck(char *str);
int av_digitaldetail(char **str);
int ft_pthreadcreate(struct s_philo *philo, int np);

# endif
