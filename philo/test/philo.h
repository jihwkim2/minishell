#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

/*
typedef struct current
{
	int current time;
	int current day;
}
*/
typedef struct s_mutex
{
	pthread_mutex_t *fork;
	pthread_mutex_t print;
	pthread_mutex_t monitoring_lock;
}	t_mutex;

typedef struct s_philo
{
	pthread_t thread;
	int num_of_philos;
	int time_to_sleep;
	int time_to_eat;
	int time_to_die;
	int last_meal;
	int monitoring_stop;
	int must_eat;
	int current_time;
	int number;
	int left;
	int deathflag;
	int right;
	long current;
	struct s_mutex *mutex;
	pthread_mutex_t *pub_mtx;
}	t_philo; 

int ft_isdigit(int num);
int av_digitcheck(char *str);
int av_digitaldetail(char **str);
int ft_pthreadcreate(struct s_philo *philo, int np);
int ft_pthreadcreate(struct s_philo *philo, int np);
void *monitoring(void *argument);
int ft_enough_eat(t_philo *philo);
int kill_philo(t_philo *philo);
int status_flag(t_philo *philo);
void stop_flag(t_philo *philo, int flag);
int ft_getfork(struct s_philo *phil);
int get_time(t_philo *philo);
void put_msg(int flag, t_philo *philo);

# endif
