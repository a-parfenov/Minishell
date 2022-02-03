/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_exe.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:43:38 by aleslie           #+#    #+#             */
/*   Updated: 2022/02/03 17:43:39 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	execute_fork(pid_t pid, char *command, char *arg[], t_obj *o)
{
	int	status;

	if (pid < 0)
	{
		perror(ERROR_NAME);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		execve(command, arg, o->env);
		micro_print_err(command);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		g_exit = WEXITSTATUS(status);
		free(command);
	}
}

void	fake_exe(t_obj *o)
{
	char	*command;
	char	*arg[3];
	pid_t	pid;

	close_fds(o->pipes->fd_in, o->pipes->fd_out, o->pipes->fd_re_out);
	close(o->pipe_fd_in);
	close(o->pipe_fd_out);
	command = find_command(o->pipes->arg);
	if (!command)
		command = ft_strdup("");
	else
		if (!ft_strchr(command, '/'))
			command = find_command_in_env(command, o);
	arg[0] = command;
	arg[1] = "";
	arg[2] = NULL;
	pid = fork();
	execute_fork(pid, command, arg, o);
}
