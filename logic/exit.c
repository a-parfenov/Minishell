/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 23:17:58 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/31 19:54:07 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	len_argvs(char **ar)
{
	int	str;

	str = 0;
	while (ar[str])
		str++;
	return (str);
}

int	is_numbers_to_string(char *str)
{
	int	i;

	i = -1;
	if (str[0] == '-')
		i++;
	while (str[++i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
	}
	return (1);
}

int	is_numbers_to_arguments(char **str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!is_numbers_to_string(str[i]))
			return (0);
	}
	return (1);
}

static int	ft_exit_util(char **code)
{
	if (is_numbers_to_string(*code))
	{
		ft_putstr_fd("exit: too many arguments\n", 1);
		return (-1);
	}
	else
	{
		ft_putstr_fd("exit\nexit: ", 1);
		ft_putstr_fd(*code, 1);
		ft_putstr_fd(": numeric argument required\n", 1);
		exit(255);
	}
	return (0);
}

int	command_exit(char **code)
{
	if (!code || !*code)
		exit(0);
	if (len_argvs(code) == 1)
	{
		if (!is_numbers_to_string(*code))
		{
			ft_putstr_fd("exit\nexit: ", 1);
			// ft_putstr_fd(*code, 1);
			// ft_putstr_fd(": numeric argument required\n", 1);
			exit(255);
		}
		else
			exit(ft_atoi(*code));
	}
	else
		return (-1);
		return (ft_exit_util(code));
	return (0);
}