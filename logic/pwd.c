/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 23:03:56 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/15 13:39:46 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	command_pwd(t_obj *o)
{
	int	i;

	i = -1;
	while (o->env[++i])
	{
		if (ft_strncmp(o->env[i], "PWD=", 4) == 0)
		{
			ft_putstr_fd(o->env[i] + 4, 1);
			ft_putstr_fd("\n", 1);
			return ;
		}
	}
}