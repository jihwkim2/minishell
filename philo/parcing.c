#include<stdio.h>
#include "philo.h"


/*
void *routine(void *argument)
{
	int num = 0;
	while (j < 100000)
	{
		
		
		printfork();mutex;
		getfork();mutex;
		eat();
		notdie(): 중간중간에 넣기
		coosleep();
		gettimeofday
		thinking();
		if 죽었을 때 종료할 수 있는 함수만들기
		
	}
}
*/

void	put_msg(char *str, t_philo *philo)
{
	pthread_mutex_lock(philo->pub_mtx);
	printf("%s\n", str);
	pthread_mutex_unlock(philo->pub_mtx);
}

int get_time(t_philo *philo)
{
	current->current_time = (&current->currentday/1000) - ((&curremt->currentday % 10) / 1000);
	return (current_time);
}

void what_time(t_philo *philo)
{
	struct timeval	time;
	gettimeofday(time);
	/* time.sec = 초
	 * time.usec = 마이크로 초*/

	philo->current =  (current_time.tv_sec / 1000) + (current.tv_usec * 1000);
}

void init_philos(t_philo *philo)
{
	if (philo->

int ft_getfork(struct s_philo *phil)
{
	pthread_mutex_lock(&phil->mutex->fork[phil->left]);
	pthread_mutex_lock(&phil->mutex->fork[phil->right]);
	put_msg("taken fork", phil);
	printf("timestamp_in_ms %d has taken a fork\n", phil->number);
	printf("timestamp_in_ms %d has taken a fork\n", phil->number);
	printf("timestamp_in_ms %d is eating\n",phil->number); 
	pthread_mutex_unlock(&phil->mutex->fork[phil->left]);
	pthread_mutex_unlock(&phil->mutex->fork[phil->right]);
	printf("timestamp_in_ms %d is sleeping\n",phil->number);
	printf("timestamp_in_ms %d is thinking\n",phil->number);
	printf("timestamp_in_ms %d died\n",phil->number);

	phil->last_meal = gettime();
	philo-> meal_eat++;

	return (0);

}

void *routine(void *argument)
{
	printf("%d",ft_getfork((struct s_philo *)argument) );
	return (NULL);


}

int ft_pthreadcreate(struct s_philo *philo, int np)
{
	pthread_mutex_t	pub_mutex;
	int				i;

	i = 0;
	pthread_mutex_init(&pub_mutex, NULL);
	while (np > i)
	{
		philo[i].pub_mtx = &pub_mutex;
		pthread_create(&(philo[i].thread), NULL, routine, &philo[i]);
		i++;
	}
	while(np > i)
	{
		pthread_join((philo[i]).thread, NULL);
		i++;
	}
	return(0);
}
