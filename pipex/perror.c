/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jihwkim2 <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 21:07:02 by jihwkim2          #+#    #+#             */
/*   Updated: 2024/10/28 21:07:29 by jihwkim2         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <errno.h>

void    perror(const char *s);

int	main(void)
{
	perror("before error");
	errno = ENOMEM;
	perror("errno = ENOMEM");
	errno = EACCES;
	perror("errno = EACCES");
	errno = ENOENT;
	perror("errno = ENOENT");
	errno = ENOTDIR;
	perror("errno = ENOTDIR");
	errno = EFAULT;
	perror("errno = EFAULT");
	errno = EBADF;
	perror("errno = EBADF");
	return (0);
}
