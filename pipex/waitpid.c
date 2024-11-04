/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waitpid.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihwkim2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:29:14 by jihwkim2          #+#    #+#             */
/*   Updated: 2024/10/28 21:41:47 by jihwkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

pid_t    waitpid(pid_t pid, int *stat_loc, int options);

int	main(void)
{
	pid_t	pid;
	int	state = 0;
	pid_t	ret;
	pid = fork();
	if (pid == 0)
	{
		sleep(1);
		ret = waitpid(-1, &state, 0);
		perror("child");
		printf("this is child\n");
	}
	else
	{
		ret = waitpid(pid, &state, 0); 
		perror("parent");              
    	printf("child pid: %d\n", ret);   
		printf("this is parent\n");
	}
	return (0);
}
