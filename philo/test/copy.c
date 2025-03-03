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
/*
void philo_to_int(t_philo **philo, char **str, int ac)
{
        int i;

        i = 0;
        while(i < philo[i]->num_of_philos)
        {
                philo[i]->num_of_philos = ft_atoi(str[1]);
                philo[i]->time_to_die = ft_atoi(str[2]);
                philo[i]->time_to_eat = ft_atoi(str[3]);
                philo[i]->time_to_sleep = ft_atoi(str[4]);
                if (ac == 6)
                        philo[i]->must_eat = ft_atoi(str[5]);
                i++;
        }
}
*/

void ft_avtoint(int ac, char **av, int num_philos, t_philo *philos)
{
	int i;

	i = 0;
	philos = malloc(sizeof(struct s_philo) * num_philos);
	while (i < num_philos)
	{
		philos[i].num_of_philos = ft_atoi(av[1]);
		philos[i].time_to_die = ft_atoi(av[2]);
		philos[i].time_to_eat = ft_atoi(av[3]);
		philos[i].time_to_sleep = ft_atoi(av[4]);
				if (ac == 6)
					philos[i].must_eat = ft_atoi(av[5]);
				else
			philos[i].must_eat = 0;
                i++;
	}
}

void ft_forklocation(int num_philos, t_philo *philos, t_mutex *mu) 
{
	int i;

	i = 0;
	while (i <= num_philos)
	{
		philos[i].number = i + 1;
		philos[i].left = i;
		philos[i].right = (i + 1) % num_philos;
		philos[i].mutex = mu;
		i++;
	}
}

void ft_mutexinit(int num_philos, t_mutex *mu)
{
	int i;

	i = 0;
	//mu->fork = malloc(sizeof(pthread_mutex_t) * num_philos);
	mu->fork = calloc(sizeof(pthread_mutex_t), num_philos);
        while(i < num_philos)
        {
                if(pthread_mutex_init(&mu->fork[i], NULL))
                {
                        printf("mutex init fail\n");
                        exit(1);
                }
                i++;
        }
        pthread_mutex_init(&mu->print, NULL);
	pthread_mutex_init(&mu->monitoring_lock, NULL);
}
#include <unistd.h>
int main(int ac, char **av)
{
	struct	s_philo philos;
	struct	s_mutex mu;
	int		i;
	int		num_philos;
 
	if (ac != 6 && ac != 5)
		return (0);
	if (av_digitaldetail(av) == 0)
		return (0);
	num_philos = ft_atoi(av[1]);
	//philos = malloc(sizeof(struct s_philo) * num_philos + 1);
	ft_avtoint(ac, av, num_philos, &philos);
	printf("1\n");
	ft_mutexinit(num_philos, &mu);
	printf("2\n");
	ft_forklocation(num_philos, &philos, &mu);
	printf("3\n");
	ft_pthreadcreate(&philos, num_philos);
	return (0);
}
