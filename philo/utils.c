#include <stdio.h>
#include "philo.h"


int ft_isdigit(int num)
{
	if (num >= '0' && num <= '9')
		return (1);
	return (0);
}

int av_digitcheck(char *str)
{
	int i = 0;

	while(str[i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}

int av_digitaldetail(char **str)
{
	int i = 1;

	while(str[i])
	{
		if (av_digitcheck(str[i]) == 0)
		{
			return (0);
		}
		i++;
	}
	return (1);
}
