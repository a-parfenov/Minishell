/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 10:42:30 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/14 12:58:02 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	if (option_n == 1)
		printf("%s ", arg[i]);
	else
	{
		printf("%s ", arg[i]);
		if (i + 1 == count_arg)
			printf("\n");
	}
}

void	command_echo(t_pipes	*pipes)
{
	int	i;
	int	option_n;
	int	count_arg;

	i = 1;
	// int j = -1;
	// while (pipes->arg[++j])
	// 	printf("|%s|\n", pipes->arg[j]);
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
	// write(1, "---\n", 4);
}