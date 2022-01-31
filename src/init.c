/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:18 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/17 10:13:01 by aleslie          ###   ########.fr       */
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

int	lst_add_back(t_obj	*o, t_env *lst)
{
	t_env	*begin;

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

void	env_struct(t_obj	*o)
{
	char	*tmp;
	int		i;

	if (!o->env_st)
	{
		i = -1;
		while (o->env[++i])
		{
			tmp = ft_strdup(o->env[i]);
			if (tmp == NULL)
				perror(" malloc");
			lst_add_back(o, lst_new_env(tmp));
			// if (ft_strncmp(tmp, "PWD=", 4) == 0)
			// 	o->pwd = &tmp[4];
			// else if ((ft_strncmp(tmp, "OLDPWD=", 7) == 0))
			// 	o->old_pwd = &tmp[7];
			// printf("+++ %s \n", o->pwd);
			// printf("+++ %s \n", o->old_pwd);
		}
	}
}

t_obj	*init_o(char **env)
{
	t_obj	*o;

	o = malloc(sizeof(t_obj));
	if (!o)
		return (NULL);
	o->is_pipe = 0;
	o->env = env;
	o->env_st = NULL;
	o->heredoc = NULL;
	o->tmp_in = -1;
	o->pipe_fd_in = -1;
	o->pipe_fd_out = -1;
	o->fd_in = -1;
	o->fd_out = -1;
	o->fd_re_out = -1;
	o->is_heredoc = 0;
	o->is_redirect = 0;
	o->is_was_dollar = 0;
	o->pipe_index = 0;
	o->parse_flag = 0;
	o->pipes = NULL;
	o->link = NULL;
	env_struct(o);
	return (o);
}

void	re_init_o_fd(t_obj *o)
{
	o->fd_in = -1;
	o->fd_out = -1;
	o->fd_re_out = -1;
	o->is_heredoc = 0;
	o->is_redirect = 0;
	o->is_was_dollar = 0;
}
