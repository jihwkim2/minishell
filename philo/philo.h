#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>



struct s_mutex
{
	pthread_mutex_t *fork;
	pthread_mutex_t print;
}	t_mutex;

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
	long current;
	struct s_mutex *mutex;
	pthread_mutex_t *pub_mtx;
}	t_philo; 

int ft_isdigit(int num);
int av_digitcheck(char *str);
int av_digitaldetail(char **str);
int ft_pthreadcreate(struct s_philo *philo, int np);

# endif
