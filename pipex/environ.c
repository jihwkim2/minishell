/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environ.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihwkim2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:04:28 by jihwkim2          #+#    #+#             */
/*   Updated: 2024/10/28 21:05:04 by jihwkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

extern char **environ;
//int main(int argc, char *argv[], char *envp[])
int	main(int argc, char *argv[])
{
	int	idx = 0;

	(void)argc;
	(void)argv;
	while (environ[idx])
	{
		printf("environ[%d]: %s\n", idx, environ[idx]);
		idx++;
	}
	return (0);
} 
