#include "philo.h"

long what_time(void)
{
	struct timeval time;
	gettimeofday(&time, NULL);

	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int fet_time(int num)
{
	long now_time;
	long timestamp;
	
	
	//philo->current = what_time();
	now_time = what_time();
	timestamp = now_time - num;
	
	return (timestamp);
	
}

#include <stdlib.h>
int main()
{
	char	*str;

	str = malloc(sizeof(char) * 5);
	str[0] = 'z';
	str[1] = 'z';
	str[2] = 'z';
	str[3] = 'z';
	str[4] = 'z';
	*str = 'z';
//	long	num;
//
//	num = what_time(); // 0
//	printf("%ld\n", num);
//	usleep(100 * 1000);
//	printf("%d\n", fet_time(num));
//	usleep(100 * 1000);
//	printf("%d\n", fet_time(num));
//	usleep(100 * 1000);
//	printf("%d", fet_time(num));
}
