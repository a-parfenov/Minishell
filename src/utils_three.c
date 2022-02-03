/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_three.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:43:51 by aleslie           #+#    #+#             */
/*   Updated: 2022/02/03 17:43:52 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_pipe_redirects(t_pipes *pipe)
{
	int		i;
	int		count;

	count = 0;
	if (pipe->is_redirect != -1)
	{
		i = 0;
		while (pipe->arg[i])
		{
			if (ft_strlen(pipe->arg[i]) == 0)
				count++;
			i++;
		}
	}
	if (pipe->is_redirect + pipe->is_was_dollar != count)
		return (1);
	return (0);
}

void	init_pipe_fds(int fd_in, int fd_out, t_obj *o)
{
	if (o->pipes->index == 0)
	{
		dup2(fd_out, 1);
		close(fd_in);
		close(fd_out);
		close(o->tmp_in);
	}
	else if (o->pipes->index == o->pipe_index - 1)
	{
		dup2(o->tmp_in, 0);
		close(fd_out);
		close(o->tmp_in);
	}
	else
	{
		dup2(fd_out, 1);
		dup2(o->tmp_in, 0);
		close(fd_out);
		close(o->tmp_in);
	}
}

int	init_logic_fd(t_obj *o)
{
	int		fd;

	fd = 1;
	if (o->is_pipe)
	{
		if (o->pipes->index == o->pipe_index - 1)
			fd = 1;
		else
		{
			dup2(o->pipe_fd_in, o->tmp_in);
			fd = o->pipe_fd_out;
		}
	}
	if (o->pipes->fd_re_out != -1)
		fd = o->pipes->fd_re_out;
	if (o->pipes->fd_out != -1)
		fd = o->pipes->fd_out;
	return (fd);
}

char	**re_build_argv(char **arg, t_obj *o)
{
	int		i;
	int		size;
	char	**res;

	i = 0;
	size = 0;
	while (arg[i])
	{
		if (ft_strlen(arg[i]) != 0)
			size++;
		i++;
	}
	res = malloc(sizeof(char *) * size + 1);
	if (!res)
		return (NULL);
	res = init_res(res, arg, o);
	return (res);
}
