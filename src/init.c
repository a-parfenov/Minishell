/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:18 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/15 14:53:52 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_env	*lst_new_env(char *arg)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (lst == NULL)
		return (NULL);
	lst->env_str = arg;
	lst->next = NULL;
	return (lst);
}

int	add_back_lst(t_obj	*o, t_env *lst)
{
	t_env *begin;

	if (lst == NULL)
		return (1);
	if (o->env_st == NULL)
		o->env_st = lst;
	else
	{
		begin = o->env_st;
		while (begin->next != NULL)
			begin = begin->next;
		begin->next = lst;
	}
	return (0);
}

t_obj	*init_o(char **env)
{
	t_obj	*o;

	o = malloc(sizeof(t_obj));
	if (!o)
		return (NULL);
	o->env = env;
	o->env_st = NULL;
	if (!o->env_st)
	{
		char *tmp;
		int i = -1;
		while (o->env[++i])
		{
			tmp = ft_strdup(o->env[i]);
			if (tmp == NULL)
				perror("malloc"); // aaaaaa
			add_back_lst(o, lst_new_env(tmp));
		}
		t_env *nn = o->env_st;
		while (nn != NULL)
		{
			printf("|| %s\n", nn->env_str);
			nn = nn->next;
		}
		write(1, "1111\n", 5);
	}
	o->heredoc = NULL;
	o->fd_in = 0;
	o->fd_out = 1;
	o->fd_re_out = 1;
	o->is_heredoc = 0;
	o->is_redirect = 0;
	o->pipes = NULL;
	o->link = NULL;
	return (o);
}
