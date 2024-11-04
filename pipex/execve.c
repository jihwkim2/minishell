/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihwkim2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 15:34:59 by jihwkim2          #+#    #+#             */
/*   Updated: 2024/10/29 16:26:22 by jihwkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

extern char **environ;

int execve(const char *path, char *const argv[], char *const envp[]);

int	main(void)
{
	char	*path = "/bin/ls";
	char	*cmd[5];

	cmd[0] = "asdfasdf";
	cmd[1] = "-a";
  cmd[2] = "-l";
	cmd[3] = NULL;
	if (execve(path, cmd, environ) < 0)
		perror(NULL);
	printf("if fail, this will be printed\n");
}
