long get_time(void) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void custom_usleep(long time_in_ms) {
    long start = get_time();
    while ((get_time() - start) < time_in_ms)
        usleep(100);
}

void print_action(t_philo *philo, char *msg) {
    pthread_mutex_lock(&philo->data->print_lock);
    printf("%ld %d %s\n", get_time() - philo->data->start_time, philo->id, msg);
    pthread_mutex_unlock(&philo->data->print_lock);
}

void eat(t_philo *philo) {
    t_data *data = philo->data;

    pthread_mutex_lock(&data->forks[philo->id]);
    print_action(philo, "has taken a fork");
    pthread_mutex_lock(&data->forks[(philo->id + 1) % data->num_philos]);
    print_action(philo, "has taken a fork");
    print_action(philo, "is eating");

    philo->last_meal_time = get_time();
    philo->meals_eaten++;
    custom_usleep(data->time_to_eat);

    pthread_mutex_unlock(&data->forks[philo->id]);
    pthread_mutex_unlock(&data->forks[(philo->id + 1) % data->num_philos]);
}

void *philo_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    t_data *data = philo->data;

    if (philo->id % 2)
        usleep(100);
    while (!data->all_ate) {
        eat(philo);
        if (data->must_eat_count && philo->meals_eaten >= data->must_eat_count) {
            data->all_ate = 1;
            break;
        }
        print_action(philo, "is sleeping");
        custom_usleep(data->time_to_sleep);
        print_action(philo, "is thinking");
    }
    return (NULL);
}

void monitor_philos(t_data *data) {
    int i;

    while (!data->all_ate) {
        i = -1;
        while (++i < data->num_philos) {
            if ((get_time() - data->philos[i].last_meal_time) > data->time_to_die) {
                print_action(&data->philos[i], "died");
                data->all_ate = 1;
                return ;
            }
        }
        usleep(1000);
    }
}

void init_philos(t_data *data) {
    int i;

    data->philos = malloc(sizeof(t_philo) * data->num_philos);
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
    i = -1;
    while (++i < data->num_philos) {
        pthread_mutex_init(&data->forks[i], NULL);
        data->philos[i].id = i;
        data->philos[i].meals_eaten = 0;
        data->philos[i].last_meal_time = get_time();
        data->philos[i].data = data;
    }
    pthread_mutex_init(&data->print_lock, NULL);
}

void start_simulation(t_data *data) {
    int i;

    data->start_time = get_time();
    i = -1;
    while (++i < data->num_philos)
        pthread_create(&data->philos[i].thread, NULL, philo_routine, &data->philos[i]);
    monitor_philos(data);
    i = -1;
    while (++i < data->num_philos)
        pthread_join(data->philos[i].thread, NULL);
}

void free_resources(t_data *data) {
    int i;

    i = -1;
    while (++i < data->num_philos)
        pthread_mutex_destroy(&data->forks[i]);
    pthread_mutex_destroy(&data->print_lock);
    free(data->forks);
    free(data->philos);
}

int main(int argc, char **argv) {
    t_data data;

    if (argc < 5 || argc > 6) {
        printf("Usage: ./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
        return (1);
    }
    data.num_philos = atoi(argv[1]);
    data.time_to_die = atol(argv[2]);
    data.time_to_eat = atol(argv[3]);
    data.time_to_sleep = atol(argv[4]);
    data.must_eat_count = (argc == 6) ? atoi(argv[5]) : 0;
    data.all_ate = 0;
    init_philos(&data);
    start_simulation(&data);
    free_resources(&data);
    return (0);
}
