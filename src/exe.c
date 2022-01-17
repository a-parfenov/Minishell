/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:10 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/17 22:18:46 by aleslie          ###   ########.fr       */
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
			command_echo(o->pipes);
		else if (ft_strncmp(o->pipes->arg[0], "cd", 2) == 0)
			command_cd(o);
		else if (ft_strncmp(o->pipes->arg[0], "exit", 4) == 0)
			command_exit(o->pipes->arg);
		else if (ft_strncmp(o->pipes->arg[0], "export", 4) == 0)
			command_export(o);
		o->pipes = o->pipes->next;
	}
	// free_pipes(&tmp);
}
