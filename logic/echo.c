/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:42:30 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/15 13:11:22 by aleslie          ###   ########.fr       */
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

void	putstr_while(char **arg, t_obj *o, int i, int option_n)
{
	int	fd;

	fd = init_logic_fd(o);
	ft_putstr_fd(arg[i], fd);
	if (arg[i + 1] && ft_strlen(arg[i]) != 0)
		ft_putchar_fd(' ', fd);
	if (i + 1 == o->count_arg && option_n == 0)
		ft_putchar_fd('\n', fd);
	g_exit = 0;
}

void	command_echo(t_pipes	*pipes, t_obj *o)
{
	int	i;
	int	option_n;

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
	while (pipes->arg[i] && !ft_strncmp(pipes->arg[i], "-n", 3))
		++i;
	o->count_arg = args_count(pipes->arg);
	while (i < o->count_arg)
		putstr_while(pipes->arg, o, i++, option_n);
}
