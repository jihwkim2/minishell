int ft_atoi(char *str)
{
	int i;
	int cmd;

	i = 0;
	cmd = 0;
	
	while(str[i])
	{
		if (str[i] >= 9 && str[i] <= 13 || str[i] == 32)
			return (0);
		else if (str[i] == '-' || str[i] == '+')
			return (0);
		else if (str[i] >= '0' && str[i] <= '9')
		{
			cmd = cmd * 10 + str[i] - '0';
		}
		i++;
	}
	return (cmd);
}

int main(int ac, char **av)
{
	if (ac == 5)
	{
		if (ft_atoi(av[2]) % 2 == 0)
		{
			if(ft_atoi(av[3]) < 2 * ft_atoi(av[4]))
				return (0);
		}
		else if (ft_atoi(av[2]) % 2 == 1)
		{
			if(ft_atoi(av[3]) < 3 * ft_atoi(av[4]))
				return (0);
		}
	}
	return (0);
}





