/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 16:38:45 by teusebio          #+#    #+#             */
/*   Updated: 2021/10/13 19:18:26 by teusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static char	*minus_exe(int n)
{
	char	*res;
	int		count;

	n = -n;
	count = count_digit(n);
	res = malloc(sizeof(char) * (count + 2));
	if (res == NULL)
		return (NULL);
	res[count + 1] = '\0';
	while (count > 0)
	{
		res[count] = n % 10 + '0';
		n /= 10;
		count--;
	}
	res[count] = '-';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		count;

	if (n == -2147483648)
		return (ft_strjoin("-21474", "83648"));
	if (n < 0)
		return (minus_exe(n));
	count = count_digit(n);
	res = malloc(sizeof(char) * (count + 1));
	if (res == NULL)
		return (NULL);
	res[count--] = '\0';
	while (count >= 0)
	{
		res[count] = n % 10 + '0';
		n /= 10;
		count--;
	}
	return (res);
}
