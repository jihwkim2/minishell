#include "philo.h"

void monitoring_stopflag(t_philo *philo, bool state)
{
	pthread_mutex_lock(&philo->)



void *monitoring(t_philo *philo)
{
	philo->deathflag = 2;
	if (philo->current_time - philo->last_meal >= philo->time_to_die)
		philo->deathflag = 1;
}

void monitoring_stop
모니터링 스레드
- 모든 철학자 모니터링
- 철학자 식사 시간 체크 + 철학자 식사 횟수 체크(식사 횟수 파라미터까지 입력받았으면)
- 모니터링 종료 조건이 충족되었으면 모든 철학자의 death_flag를 true로 만들고 스레드 종료

