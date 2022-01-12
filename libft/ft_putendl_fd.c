/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 09:03:26 by teusebio          #+#    #+#             */
/*   Updated: 2021/10/11 12:51:50 by teusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (fd != -1 && s != NULL)
	{
		while (*s)
			write (fd, s++, 1);
		write(fd, "\n", 1);
	}
}
