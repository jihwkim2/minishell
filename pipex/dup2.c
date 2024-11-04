/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihwkim2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:45:12 by jihwkim2          #+#    #+#             */
/*   Updated: 2024/10/28 21:45:40 by jihwkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int    dup2(int fildes, int fildes2);

int	main(void)
{
	int	fd = open("newfile", O_RDWR | O_CREAT, 0644);
	printf("printf before dup2\n");
	dup2(fd, STDOUT_FILENO);
	printf("printf after dup2\n");
	close(fd);
	return (0);
}
