#include "philo.h"

void stop_flag(t_philo *philo, bool status)
{
	pthread_mutex_lock(&philo->monitoring_lock);
	philo->monitoring_stop = status;
	pthread_mutex_unlock(&philo->monitoring_lock);
}

bool status_flag(t_philo *philo)
{
	bool r;

	r = false;
	pthread_mutex_lock(&philo->monitoring_lock);
	if (philo->monitoring_stop == true)
		r = true;
	pthread_utex_unlock(&philo->monitoring_lock);
	return (r);
}

bool kill_philo(t_philo *philo)
{
	int time;

	time = get_time(philo);
	if (time - philo->last_meal >= time_to_die)
	{
		stop_flag(philo, true);
		put_msg(5, philo); 
		//flag를 어떻게 받을 지 생각해야됨
		return (true);
	}
	return (false);
}

bool ft_enough_eat(t_philo *philo)
{
	unsigned int i;
	bool enough_eat;

	enough_eat = true;
	i = 0;
	while (i < philo->num_of_philos)
	{
		pthread_mutex_lock(philo[i].monitoring_lock);
		if (kill_philo(philo) == true)
			return (true);
		if(philo->time_to_eat < philo->must_eat)
			enough_eat = false;
		pthread_mutex_unlock(philo[i].monitoring_lock);
		i++;
	}
	if (enough_eat ==true)
	{
		stop_flag(philo,true);
		return(true);
	}
	return(false);
}

void *monitoring(t_philo *philo)
{
	if(philo->must_eat == 0)
		return (NULL);
	stop_flag(philo, false);


}


