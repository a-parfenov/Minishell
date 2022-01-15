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

void	exe(t_obj *o)
{
	// t_pipes *tmp = o->pipes->arg;
	
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
		else if (ft_strncmp(o->pipes->arg[0], "cd", 2) == 0)
			command_cd(o);
		o->pipes = o->pipes->next;
	}
	// free_pipes(&tmp);
}
