/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 23:30:21 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/17 22:26:17 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*min_max_export(t_env *tmp, int flag)
{
	t_env	*min_max;
	int		n;

	min_max = tmp;
	while (tmp != NULL)
	{
		n = ft_strcmp(tmp->env_str, tmp->next->env_str);
		if(flag == MIN && tmp->next && 0 > n)
			min_max = tmp;
		if(flag == MAX && tmp->next && 0 < n)
			min_max = tmp;
		tmp = tmp->next;
	}
	printf("%s\n", min_max->env_str);
	return (min_max);
}

t_env	*sort_env_for_export(t_env	*min)
{
	t_env	*start;
	t_env	*tmp;

	start = min;
	tmp = min_max_export(min, MAX);
	if (tmp == min)
		return (NULL);
	while (start != NULL)
	{
		if (ft_strcmp(start->env_str, tmp->env_str) < 0
			&& ft_strcmp(start->env_str, min->env_str) > 0)
			tmp = start;
		start = start->next;
	}
	return (tmp);
}

void	command_export(t_obj *o)
{
	t_env	*max;
	t_env	*min;

	ft_putstr_fd("11111111\n\n", 1);
	min = min_max_export(o->env_st, MIN);
	o->env_export = min;
	max = min_max_export(o->env_st, MAX);
	ft_putstr_fd("111222333311111\n\n", 1);
	while (min != max)
	{
		min->export_next = sort_env_for_export(min);
		min = min->next;
	}
	t_env	*tmp;
	ft_putstr_fd("11111111\n\n", 1);
	tmp = o->env_export;
	while (tmp != NULL)
	{
		ft_putendl_fd(tmp->env_str, 1);
		tmp = tmp->next;
	}
	ft_putstr_fd("111222211111\n\n", 1);
}

