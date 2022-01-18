/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 23:30:21 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/18 16:45:53 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*min_max_export(t_env *var, int flag)
{
	t_env	*tmp;
	t_env	*min;
	int		n;

	tmp = var;
	min = var;
	while (tmp != NULL)
	{
		n = ft_strcmp(min->env_str, tmp->env_str);
		if(flag == MAX && n < 0)
			min = tmp;
		if(flag == MIN && n > 0)
			min = tmp;
		tmp = tmp->next;
	}
	// printf("****    \033[1;32m %s\033[0m\n", min->env_str);
	return (min);
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

void	sort_env(t_obj *o)
{
	t_env	*max;
	t_env	*min;

	// ft_putstr_fd("11111111\n\n", 1);
	min = min_max_export(o->env_st, MIN);
	o->env_export = min;
	max = min_max_export(o->env_st, MAX);
	// ft_putstr_fd("111222333311111\n\n", 1);
	while (min != max)
	{
		min->export_next = sort_env_for_export(min);
		min = min->next;
	}
	// t_env	*tmp;
	// ft_putstr_fd("11111111\n\n", 1);
	// tmp = o->env_export;
	// while (tmp != NULL)
	// {
	// 	ft_putendl_fd(tmp->env_str, 1);
	// 	tmp = tmp->next;
	// }
	// ft_putstr_fd("111222211111\n\n", 1);
}

// t_env	*min_max_export(t_env *var, int flag)
// {
// 	t_env	*tmp;
// 	t_env	*min;
// 	// int		n;

// 	tmp = var;
// 	min = var;
// 	printf("****    \033[1;32m %s\033[0m\n", min->env_str);
// 	while (tmp != NULL)
// 	{
// 		int i = 0;
// 		// n = ft_strcmp(min->env_str, tmp->env_str);
// 		while (min->env_str[i] != '='|| tmp->env_str[i] != '=')
// 		{
// 			// write(1, "xxxxx-------33\n", 10);
// 			// if(flag == MAX && (min->env_str[i] - tmp->env_str[i]) < 0)
// 			// {
// 			// 	min = tmp;
// 			// 	break;
// 			// }
// 			if(flag == MIN && (min->env_str[i] - tmp->env_str[i]) > 0)
// 			{
// 				min = tmp;
// 				break;
// 			}
// 			++i;
// 		}
// 		tmp = tmp->next;
// 	}
// 	printf("++++    \033[1;32m %s\033[0m\n", min->env_str);
// 	return (min);
// }

// t_env	*sort_env_for_export(t_env	*min)
// {
// 	t_env	*start;
// 	t_env	*tmp;

// 	start = min;
// 	tmp = min;
// 	if (tmp == min)
// 		return (NULL);
// 	while (start != NULL)
// 	{
// 		int i = 0;
// 		write(1, "-------33\n", 10);
// 		while (start->env_str[i] != '='|| tmp->env_str[i] != '=')
// 		{
// 			write(1, "----444\n", 8);
// 			// if (ft_strcmp(&start->env_str[i], &tmp->env_str[i]) < 0
// 			// 	&& ft_strcmp(&start->env_str[i], &min->env_str[i]) > 0)
// 			if (start->env_str[i] < tmp->env_str[i])
// 			{
// 				tmp = start;
// 				break;
// 			}
// 			++i;
// 		}
// 		start = start->next;
// 	}
// 	return (tmp);
// }

// void	command_export(t_obj *o)
// {
// 	t_env	*max;
// 	t_env	*min;

// 	write(1, "---------------\n\n", 17);
// 	// min = min_max_export(o->env_st, MIN);
// 	min = o->env_st;
// 	// o->env_export = min;
// 	max = min_max_export(o->env_st, MAX);
// 	write(1, "\n\033[1;32m----- *** -----\033[0m\n\n", 30);
// 	while (min != max)
// 	{
// 		min->export_next = sort_env_for_export(min);
// 		min = min->next;
// 		printf("++------++\n");
// 	}
	
// 	t_env	*tmp;
// 	write(1, "\n\033[1;32m----- --- -----\033[0m\n\n", 30);
// 	tmp = o->env_export;
// 	while (tmp != NULL)
// 	{
// 		ft_putendl_fd(tmp->env_str, 1);
// 		tmp = tmp->next;
// 	}
// 	write(1, "\n\033[1;32m----- --- -----\033[0m\n\n", 30);
// }