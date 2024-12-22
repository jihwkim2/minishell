#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
/*
	
 */
/*
process
	a.out (프로그램)
	실행하면 프로세스.
	실행중인 프로그램을 나타냄
	프로그램의 실행 단위

thread
	프로그램을 실해아면 처리하는 애들이 필요..
	프로그램의 작업을 처리하는 주체.
		때문에 프로세스 하나당 하나의 스레드를 무조건 필요..
	'하나 이상의' 스레드가 필요..
	하나 이상의 스레드로 동작하는 프로그램은 뭐라고 하나요.
		멀티스레딩 프로그램
		멀티스레딩 프로세스
 */

/*== 둘(thread or process)의 통신 ==*/
/*
thread.
	하나의 프로그램에서 작업을 실행하는 주체: 스레드.
	=
	하나의 프로그램 안에서 스레드들이 동작한다.
	=
	동작중인 프로세스 내에서 같은 메모리를 스레드들이 참조할 수 있다.



프로세스는 메모리 공간을 할당 받음.
	(프로세스 내에서 스레드들이 일함.)
=
프로세스끼리는 메모리를 공유하지 않음.
=
프로세스끼리의 통신은 별도의 통신작업이 필요함
 */

pthread_mutex_t	mutex_1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t	mutex_2 = PTHREAD_MUTEX_INITIALIZER;
int	num = 0;

// ./philo 4 310 100 100
int philos = 4; // 그룹 2개

// ./philo 5 310 100 100
philos = 5; // 그룹 3개

typedef struct s_philo
{
	pthead_t thread;
	pthread_mutex_t mutex;
	int 	num of philos; // 5
	int			time to sleep; // 100
	int			time to eat; // 100
	int			time to die; // 210
}

void	*routine(void *argument)
{
	printf("I'm in thread\n");
	printf("%d\n", (int *)arg);

	int	i;
	i = 0;

//	pthread_mutex_lock(&mutex_1);
	printf("lock mutex\n");
	while (i < 1000000)
	{
		num++;
		i++;
	}
	printf("%d\n", num);
//	pthread_mutex_unlock(&mutex_1);
	return (0);
}

int	main(void)
{
	int	i;

	i = 0;
	struct s_philo *philo;
	philo = malloc(sizeof(pthread_t) * philo->num_of_philos);

	while (i < num_of_philos)
	{
		pthread_create(philo->thread[i], NULL, routine, (void *)philo[i]);

		i++;
	}
	i = 0;
	while(i < philo->num_of_philos)
	{
		pthread_join

	pthread_t	thread_1;
	pthread_t	thread_2;

	pthread_create(&thread_1, NULL, routine, (long *)1);
	pthread_create(&thread_2, NULL, routine, (long *)2);
	pthread_join(thread_1, NULL);
	printf("thread_1 end\n");
	pthread_join(thread_2, NULL);
	printf("main wait\n");
	printf("%d\n", num);
	return (0);
}
