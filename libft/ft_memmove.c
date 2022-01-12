/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:55:34 by teusebio          #+#    #+#             */
/*   Updated: 2021/10/15 19:22:45 by teusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*chd;
	char	*chs;

	chd = (char *)dst;
	chs = (char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (chd <= chs)
	{
		while (len--)
			*chd++ = *chs++;
	}
	else
	{
		chd = (char *)dst + len - 1;
		chs = (char *)src + len - 1;
		while (len--)
			*chd-- = *chs--;
	}
	return (dst);
}
