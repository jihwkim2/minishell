#include "philo.h"

void destroy_mutex(t_philo *philo)
{
	unisigned int i;

	i = 0;
	while(i < philo->num_of_philos)
	{
		pthread_mutex_destroy(&philo->fork[i]);
		i++;
	}
	pthread_mutex_destroy(&philo->pub_mtx);
	pthread_mutex_destroy(&philo->print);
}


	                

