/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strtrim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 17:11:14 by teusebio          #+#    #+#             */
/*   Updated: 2021/10/14 09:50:48 by teusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*find_start(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i])
	{
		while (set[j])
		{
			if (s1[i] == set[j])
			{
				i++;
				j = 0;
			}
			else
				j++;
		}
		return ((char *)s1 + i);
	}
	return (NULL);
}

static char	*find_end(const char *s1, const char *set)
{
	int	i;
	int	j;

	i = ft_strlen(s1) - 1;
	j = ft_strlen(set) - 1;
	while (i >= 0)
	{
		while (j >= 0)
		{
			if (s1[i] == set[j])
			{
				i--;
				j = ft_strlen(set) - 1;
			}
			else
				j--;
		}
		return ((char *)s1 + i + 1);
	}
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	char	*start;
	char	*end;
	int		i;

	if (NULL == s1)
		return (NULL);
	i = 0;
	start = find_start(s1, set);
	if (s1[i] == '\0' || start[i] == '\0')
	{
		res = malloc(sizeof(char) * 1);
		res[0] = '\0';
		return (res);
	}
	end = find_end(s1, set);
	res = malloc(sizeof(char) * (end - start + 1));
	if (NULL == res)
		return (NULL);
	while (start < end)
		res[i++] = *start++;
	res[i] = '\0';
	return (res);
}
