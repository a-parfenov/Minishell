/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:10 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/14 11:47:36 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//void	exe(t_obj *o)
//{
//	t_pipes *tmp = o->pipes;
//
//	while (o->pipes)
//	{
//		while (o->pipes->link)
//		{
//			if (ft_strncmp(o->pipes->link->str, "env", 3) == 0)
//				command_env(o);
//			else if (ft_strncmp(o->pipes->link->str, "pwd", 3) == 0)
//				command_pwd(o);
//			else if (ft_strncmp(o->pipes->link->str, "echo", 4) == 0)
//				// command_echo(sp);
//			o->pipes->link = o->pipes->link->next;
//		}
//		o->pipes = o->pipes->next;
//	}
//	free_pipes(&tmp);
//}
