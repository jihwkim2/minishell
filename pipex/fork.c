/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihwkim2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:45:43 by jihwkim2          #+#    #+#             */
/*   Updated: 2024/10/28 21:23:20 by jihwkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

int ft_asda(char *av, char **envp)
{
    pid_t pid;

    pid = fork();

    if (pid == -1)
    {
        printf("fork() error");
        exit(1);
    }
    if (pid == 0)
    {
        printf("\n****자식프로세스****\n");
        printf("변수pid값: %d\n", pid);
        printf("자식피드: %d\n", getpid());
    }
	else
    {
        printf("\n****부모프로세스****\n");
        printf("변수pid값: %d\n", pid);
        printf("부모피드: %d\n", getpid());
    }
    return (0);
}

int main(int ac, char **av, char **envp)
{
	pid_t pid;
	int i = 0;

	while (i < ac - 1)
	{
		ft_asda(av[i++], envp);
	 
	}
	return (0);
}



