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

int ft_getfork(struct s_philo *phil)
{
	pthread_mutex_lock(&phil->mutex->fork[phil->left]);
	pthread_mutex_lock(&phil->mutex->fork[phil->right]);
	printf("timestamp_in_ms %d has taken a fork\n", phil->number);
	printf("timestamp_in_ms %d has taken a fork\n", phil->number);
	printf("timestamp_in_ms %d is eating\n",phil->number); 
	pthread_mutex_unlock(&phil->mutex->fork[phil->left]);
	pthread_mutex_unlock(&phil->mutex->fork[phil->right]);
	printf("timestamp_in_ms %d is sleeping\n",phil->number);
	printf("timestamp_in_ms %d is thinking\n",phil->number);
	printf("timestamp_in_ms %d died\n",phil->number);
	return (0);

}
		




void *routine(void *argument)
{

	printf("%d",ft_getfork((struct s_philo *)argument) );
}
	

	

int ft_pthreadcreate(struct s_philo *philo, int np)
{

	int i = 0;
	while (np > i)
	{
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
