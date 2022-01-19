/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:10 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/14 22:02:45 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exe_pipes(char **arg, t_obj *o)
{
	printf("hello exe_pipes %s %s\n", arg[0], o->pipes->arg[0]);
}

void	exe(t_obj *o)
{
	int	size;

	size = pipes_size(o->pipes);
	printf("pipes size %d\n", size);
	while (o->pipes)
	{
		if (ft_strncmp(o->pipes->arg[0], "env", 3) == 0)
			command_env(o);
		else if (ft_strncmp(o->pipes->arg[0], "pwd", 3) == 0)
			command_pwd(o);
		else if (ft_strncmp(o->pipes->arg[0], "echo", 4) == 0)
		{
			// write(1, "\n+++\n", 5);
			command_echo(o->pipes);
		}
		else if (ft_strncmp(o->pipes->arg[0], "cd", 2) == 0) {
			command_cd(o);
		}
		else
		{
			if (size == 1)
				exe_single_command(o);
			else
				exe_pipes(o->pipes->arg, o);
		}
		o->pipes = o->pipes->next;
	}
}
