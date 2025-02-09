#include <stdio.h>
#include "philo.h"

int ft_atoi(char *str)
{
        int i;
        long long cmd;

        i = 0;
        cmd = 0;

        while(str[i])
        {
                cmd = cmd * 10 + str[i] - '0';
                i++;
        }
	if (cmd > 2147483647)
		return (0);
        return (cmd);
}

int main(int ac, char **av)
{
	struct s_philo *philos;
	int		num_of_philos;
	struct s_mutex mu;
	int i;

	if (ac != 6 && ac != 5)
		return (0);
	if (av_digitaldetail(av) == 0)
		return (0);
	num_of_philos = ft_atoi(av[1]);
	philos = malloc(sizeof(struct s_philo) * num_of_philos);
	i = 0;
	while(i < num_of_philos)
	{
		philos[i].num_of_philos = ft_atoi(av[1]);
		philos[i].time_of_die = ft_atoi(av[2]);
		philos[i].time_of_eat = ft_atoi(av[3]);
		philos[i].time_of_sleep = ft_atoi(av[4]);
		if (ac == 6)
			philos[i].must_eat = ft_atoi(av[5]);
		i++;
	}
	i = 0;
	mu.fork = malloc(sizeof(pthread_mutex_t) * num_of_philos);
	while(i < num_of_philos)
	{
		pthread_mutex_init(&mu.fork[i], NULL);
		i++;
	}
	pthread_mutex_init(&mu.print, NULL);
	i = 0;
	while (i < num_of_philos)
	{
		philos[i].number = i + 1;
		philos[i].left = i;
		philos[i].right = (i + 1) % num_of_philos;
		philos[i].mutex = &mu;
		i++;
	}
	ft_pthreadcreate(philos, num_of_philos);
	

	return (0);
}
