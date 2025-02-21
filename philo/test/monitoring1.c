#include "philo.h"

void stop_flag(t_philo *philo, int flag)
{
		printf("stop flg\n");
        pthread_mutex_lock(&philo->mutex->monitoring_lock);
		printf("stop flg\n");
        philo->monitoring_stop = flag;
        pthread_mutex_unlock(&philo->mutex->monitoring_lock);
}

int status_flag(t_philo *philo)
{
        int r;

        r = 2;
        pthread_mutex_lock(&philo->mutex->monitoring_lock);
        if (philo->monitoring_stop == 1)
                r = 1;
        pthread_mutex_unlock(&philo->mutex->monitoring_lock);
        return (r);
}

int kill_philo(t_philo *philo)
{
        int time;
		t_mutex *mutex;

        time = get_time(philo);
        if (time - philo->last_meal > philo->time_to_die)
        {
                stop_flag(philo, 1);
                put_msg(5, philo);
				return (1);
        }
        return (2);
}

int ft_enough_eat(t_philo *philo)
{
	unsigned int i;
	int enough_eat;
	
	enough_eat = 1;
	i = 0;
	while (i < philo->num_of_philos)
    {
		pthread_mutex_lock(&philo[i].mutex->monitoring_lock);
		if (kill_philo(philo) == 1)
			return (1);
	/*
	if (philo->must_eat != 0)
	{
		//if(philo->time_to_eat < philo->must_eat_count)
    	enough_eat = 2;
	}
	*/
		pthread_mutex_unlock(&philo[i].mutex->monitoring_lock);
			i++;
	}
	if (enough_eat == 1)
	{
	        stop_flag(philo,1);
	        return(1);
	}
	return(2);
}

void *monitoring(void *argument)
{
        t_philo *philo;

        philo = (t_philo *)argument;
		printf("inin\n");
        if(philo->must_eat == 0)
                return (NULL);
		printf("inin2\n");
        stop_flag(philo, 2);
		printf("inin3\n");
        while(kill_philo(philo) == 1)
        {
			printf("inin4\n");
                if (ft_enough_eat(philo) == 1)
                        return (NULL);
                usleep(1000);
        }
			printf("inin4-1\n");
        return (NULL);
}
