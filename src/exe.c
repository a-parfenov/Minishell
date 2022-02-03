/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:10 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/17 22:18:46 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	init_o_fds(t_obj *o)
{
	int		pipe_fd[2];

	if (o->is_pipe)
	{
		if (pipe(pipe_fd) < 0)
		{
			perror(ERROR_NAME);
			return ;
		}
		o->pipe_fd_in = pipe_fd[0];
		o->pipe_fd_out = pipe_fd[1];
	}
}

void	single(t_obj *o)
{
	if (!o->pipes->arg[0])
		return ;
	init_o_fds(o);
	if (ft_strncmp(o->pipes->arg[0], "env", 3) == 0)
		command_env(o);
	else if (ft_strncmp(o->pipes->arg[0], "pwd", 3) == 0)
		command_pwd(o);
	else if (ft_strncmp(o->pipes->arg[0], "echo", 4) == 0)
		command_echo(o->pipes, o);
	else if (ft_strncmp(o->pipes->arg[0], "cd", 2) == 0)
		command_cd(o);
	else if (ft_strncmp(o->pipes->arg[0], "exit", 4) == 0)
		command_exit(o->pipes->arg, o);
	else if (ft_strncmp(o->pipes->arg[0], "export", 4) == 0)
		command_export(o);
	else if (ft_strncmp(o->pipes->arg[0], "unset", 5) == 0)
		command_unset(o);
	else
		exe_command(o);
	close(o->pipe_fd_in);
	close(o->pipe_fd_out);
}

void	exe(t_obj *o)
{
	int	size;
	int	p_fd[2];

	size = pipes_size(o->pipes);
	if (size == 1)
		single(o);
	else
	{
		if (pipe(p_fd) < 0)
		{
			perror(ERROR_NAME);
			return ;
		}
		close(p_fd[1]);
		o->tmp_in = p_fd[0];
		while (o->pipes)
		{
			single(o);
			o->pipes = o->pipes->next;
		}
		o->is_pipe = 0;
		close(o->tmp_in);
	}
	o->pipe_index = 0;
}
