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

long what_time(void)
{
	struct timeval	time;
	gettimeofday(&time, NULL);
	/* time.sec = 초
	 * time.usec = 마이크로 초*/

//	philo->current =  (time.tv_sec / 1000) + (time.tv_usec * 1000);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int get_time(t_philo *philo)
{
	long	now_time;
	long	timestamp;


	now_time = what_time();
	timestamp = now_time - philo->current;
	return (timestamp);
}

void	put_msg(int flag, t_philo *philo)
{
	pthread_mutex_lock(philo->pub_mtx);
	if (flag == 1)
		printf("%dms %d is eating\n", get_time(philo), philo->number);
	else if (flag == 2)
		printf("%dms %d is sleeping\n", get_time(philo), philo->number);
	else if (flag == 3)
		printf("%dms %d is thinking\n", get_time(philo), philo->number);
	else if (flag == 4)
		printf("%dms %d has taken a fork\n", get_time(philo), philo->number);
	else if (flag == 5)
		printf("%dms %d died\n", get_time(philo), philo->number);
	pthread_mutex_unlock(philo->pub_mtx);
}

void mili_sleep(int time_to_sleep, t_philo *philo)
{
	usleep(time_to_sleep * 1000);
}
// ./philo 2 210 100 50
int ft_getfork(struct s_philo *phil)
{
	if (phil->number % 2 == 0)
		mili_sleep(phil->time_of_eat - 10, phil);
	pthread_mutex_lock(&phil->mutex->fork[phil->left]);	
	put_msg(4, phil);
	pthread_mutex_lock(&phil->mutex->fork[phil->right]);	
	put_msg(4, phil);
	put_msg(1, phil);
	mili_sleep(phil->time_of_eat, phil);
	pthread_mutex_unlock(&phil->mutex->fork[phil->left]);
	pthread_mutex_unlock(&phil->mutex->fork[phil->right]);	
	put_msg(2, phil);
	mili_sleep(phil->time_of_sleep, phil);
	put_msg(3, phil);

//	put_msg(5, phil);

//	phil->last_meal = gettime();
//	philo-> meal_eat++;

	return (0);

}

void *routine(void *argument)
{
	ft_getfork((struct s_philo *)argument);
	return (NULL);
}

int ft_pthreadcreate(struct s_philo *philo, int np)
{
	pthread_mutex_t	pub_mutex;
	int				i;

	i = 0;
	pthread_mutex_init(&pub_mutex, NULL);
	//philo->current = what_time();
	while (np > i)
	{
		philo[i].pub_mtx = &pub_mutex;
		philo[i].current = what_time();
		pthread_create(&(philo[i].thread), NULL, routine, &philo[i]);
		i++;
	}
	i = 0;
	while(np > i)
	{
		pthread_join((philo[i]).thread, NULL); // thread를 기다림.
											   // main thread
		i++;
	}
	return(0);
}
