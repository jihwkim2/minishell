#include "philo.h"

void stop_flag(t_philo *philo, int flag)
{
        pthread_mutex_lock(&philo->mutex->monitoring_lock);
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

        time = get_time(philo);
        if (time - philo->last_meal > philo->time_to_die)
        {
                stop_flag(philo, 1);
                put_msg(5, philo);
                //flag를 어떻게 받을 지 생각해야됨
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
		//if (philo->must_eat != -1)
		//{
		if(philo->time_to_eat < philo->must_eat)
                        	enough_eat = 2;
		//}
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
        if(philo->must_eat == 0)
                return (NULL);
        stop_flag(philo, 2);
        while(kill_philo(philo) == 1)
        {
                if (ft_enough_eat(philo) == 1)
                        return (NULL);
                usleep(1000);
        }
        return (NULL);
}
