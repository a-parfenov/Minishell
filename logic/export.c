/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:54:28 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/18 16:49:16 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	str_index(char *str, char c)
{
	int		index;

	index = -1;
	while (str[++index])
	{
		if (str[index] == c)
			return (index);
	}
	return (index);
}

void	print_export(t_obj *o)
{
	t_env	*tmp;

	tmp = o->env_export;
	while (tmp != NULL)
	{
		// if (o->env_export->env_str && o->env_export->env_str[0])
		printf("declare -x %s\n", tmp->env_str);
		tmp = tmp->next;
	}
}

void	command_export(t_obj *o)
{
	// if (!o->env[1])
	print_export(o);
	// int i = -1;
	// int index;
	// while (o->env[++i])
	// {
	// 	index = str_index(o->env[i], '=');
	// 	// in_export_while(av, env, index_eq, i);
	// }


}
