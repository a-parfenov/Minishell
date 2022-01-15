/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:42:30 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/14 22:16:57 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	args_count(char **arg)
{
	int	count;

	count = 0;
	while (arg[count])
	{
		count++;
	}
	return (count);
}

void	putstr_while(char **arg, int count_arg, int i, int option_n)
{
	ft_putstr_fd(arg[i], 1);
	if (arg[i + 1])
		ft_putchar_fd(' ', 1);
	if (i + 1 == count_arg && option_n == 0)
		ft_putchar_fd('\n', 1);
}

void	command_echo(t_pipes	*pipes)
{
	int	i;
	int	option_n;
	int	count_arg;

	i = 1;
	option_n = 0;
	if (!pipes->arg[1])
	{
		write(1, "\n", 1);
		return ;
	}
	if (pipes->arg[1][0] == '-' && pipes->arg[1][1] == 'n'
		&& pipes->arg[1][2] == '\0')
	{
		option_n = 1;
		i++;
	}
	count_arg = args_count(pipes->arg);
	while (i < count_arg)
	{
		putstr_while(pipes->arg, count_arg, i, option_n);
		i++;
	}
}