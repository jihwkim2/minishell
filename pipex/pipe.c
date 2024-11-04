/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihwkim2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:48:38 by jihwkim2          #+#    #+#             */
/*   Updated: 2024/10/28 21:49:25 by jihwkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

int pipe(int fildes[2]);

int	main(void)
{
	int	pipefd[2];
	pipe(pipefd);
	pid_t	child_pid = fork();
	if (child_pid == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		printf("this is child\n");
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		char	*buff = calloc(100, sizeof(char));
		read(0, buff, 10);
		printf("this is parent, read from pipe: %s\n", buff);
		free(buff);
	}
	return (0);
}
