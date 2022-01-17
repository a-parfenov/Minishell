/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:31:12 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/17 14:29:33 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	command_env(t_obj	*o)
{
	// int	i;

	// i = -1;
	// write(1, "\n", 1);
	// write(1, "\n", 1);
	// while (o->env[++i])
	// 	ft_putendl_fd(o->env[i], 1);
	// write(1, "\n", 1);
	// write(1, "\n", 1);
	t_env	*tmp;

	tmp = o->env_st;
	while (tmp != NULL)
	{
		ft_putendl_fd(tmp->env_str, 1);
		tmp = tmp->next;
	}
	// write(1, "\n", 1);
	// write(1, "\n", 1);
}
