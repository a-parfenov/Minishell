/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:31:12 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/13 23:15:45 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command_env(t_obj	*o)
{
	int	i;

	i = -1;
	while (o->env[++i])
		ft_putendl_fd(o->env[i], 1);
}