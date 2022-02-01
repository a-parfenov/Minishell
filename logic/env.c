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
	int		fd;

	if (o->is_pipe)
	{
		printf("hello %d %d %d\n", o->pipe_fd_out, o->pipes->fd_re_out, o->pipes->fd_out);
		fd = o->pipe_fd_out;
	}
	if (o->pipes->fd_re_out != -1)
		fd = o->pipes->fd_re_out;
	if (o->pipes->fd_out != -1)
		fd = o->pipes->fd_out;
	tmp = o->env_st;
	while (tmp != NULL)
	{
		ft_putendl_fd(tmp->env_str, fd);
		tmp = tmp->next;
	}
	close_fds(o->pipes->fd_in, o->pipes->fd_out, o->pipes->fd_re_out);
	close(o->pipe_fd_in);
	close(o->pipe_fd_out);
	// write(1, "\n", 1);
	// write(1, "\n", 1);
}
