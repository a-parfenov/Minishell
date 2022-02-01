/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 15:54:28 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/26 16:25:48 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_for_error_data(char *data, char c)
{
	int	i;

	i = 0;
	while (data[i])
	{
		if (!(ft_isalpha(data[i]) || data[i] == '_' ) || (data[i] == '='))
			break ;
		i++;
	}
	if (data[i] && data[i] != '=')
	{
		if (c == 'e')
			ft_putstr_fd("minishell: export: `", 2);
		else if (c == 'u')
			ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(data, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		g_exit = 1;
		return (1);
	}
	return (0);
}

t_env	*find_env_data(t_env *env, char *data)
{
	int	len;

	if (ft_strchr(data, '='))
		len = ft_strchr_len(data, '=');
	else
		len = ft_strlen(data);
	while (env)
	{
		if (!ft_strncmp(data, env->env_str, len)
			&& (env->env_str[len] == '=' || !env->env_str[len]))
			return (env);
		env = env->next;
	}
	return (NULL);
}

void	add_new_data(t_obj *o, char *command)
{
	t_env	*list;

	list = find_env_data(o->env_st, command);
	if (list)
	{
		if (ft_strchr(command, '='))
		{
			free(list->env_str);
			list->env_str = ft_strdup(command);
		}
	}
	else
		lst_add_back(o, lst_new_env(ft_strdup(command)));
}

void	command_export(t_obj *o)
{
	int	a;

	if (!o->pipes->arg[1])
		sort_env(o);
	else
	{
		a = 1;
		while (o->pipes->arg[a])
		{
			if (check_for_error_data(o->pipes->arg[a], 'e'))
				;
			else
			{
				add_new_data(o, o->pipes->arg[a]);
				g_exit = 0;
			}
			a++;
		}
	}
}
