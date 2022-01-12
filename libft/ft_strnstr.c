/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strnstr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 09:28:13 by teusebio          #+#    #+#             */
/*   Updated: 2021/10/13 15:39:43 by teusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	nlen;
	int		res;

	i = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	nlen = ft_strlen(needle);
	while (haystack[i] && i < len)
	{
		if (haystack[i] == needle[0])
		{
			if (i + nlen > len)
				return (NULL);
			res = ft_strncmp((char *)(haystack + i), (char *)needle, nlen);
			if (res == 0)
				return ((char *)(haystack + i));
		}
		i++;
	}
	return (NULL);
}
