/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 23:30:21 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/14 23:37:48 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	command_export(t_obj *o)
{
	char	**export;
	
	if (!o->pipes->arg[1])
	{
		show_sorted_env(o->pipes->arg);
		return (0);
	}
	else
	{		
		export = ft_split(!o->pipes->arg[1], '=');
		paste_env(export2, envr);
		return (0);
	}
}