/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:26:38 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/26 11:46:47 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	next_env(t_env *orig, t_env *new)
{
	t_env	*last;

	while (orig->next)
	{
		if (orig->next && !ft_strncmp(orig->next->env_str,
				new->env_str, ft_strlen(orig->next->env_str)))
		{
			last = orig->next;
			orig->next = orig->next->next;
			last->next = NULL;
		}
		else
			orig = orig->next;
	}
	if (last)
	{
		free(last->env_str);
		free(last);
	}
}

static t_env	*copy_env(t_env *env)
{
	t_env	*orig;

	orig = env->next;
	free(env->env_str);
	env->env_str = NULL;
	free(env);
	env = NULL;
	return (orig);
}

void	command_unset(t_obj *o)
{
	t_env	*new;
	int		i;

	if (!(o->pipes->arg[1]))
		return ;
	i = 0;
	g_exit = 0;
	while (o->pipes->arg[++i])
	{
		if (check_for_error_data(o->pipes->arg[i], 'u'))
			;
		new = find_env_data(o->env_st, o->pipes->arg[i]);
		if (new)
		{
			if (!ft_strncmp(o->env_st->env_str, new->env_str,
					ft_strlen(o->env_st->env_str)))
				o->env_st = copy_env(o->env_st);
			else
				next_env(o->env_st, new);
		}
	}
}
