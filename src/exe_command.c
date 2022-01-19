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

char	**init_res(char **res, char **arg)
{
	int		i;
	int		size;

	i = 0;
	size = 0;
	while (arg[i])
	{
		if (ft_strlen(arg[i]) != 0)
			res[size++] = ft_strdup(arg[i]);
		i++;
	}
	res[size] = NULL;
	if (!ft_strchr(res[0], '/'))
		res[0] = find_command_in_env(res[0]);
	return (res);
}

char	**re_build_argv(char **arg)
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
	res = init_res(res, arg);
	return (res);
}

void	exe_fork(char *command, t_obj *o)
{
	char	**argv;
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
	{
		perror(ERROR_NAME);
		exit(1);
	}
	else if (pid == 0)
	{
		argv = re_build_argv(o->pipes->arg);
		if (o->pipes->heredoc)
			exe_heredoc(o->pipes);
		init_fds(o->pipes->fd_in, o->pipes->fd_out, o->pipes->fd_re_out);
		execve(argv[0], argv, o->env);
		micro_print_err(command);
		exit(EXIT_FAILURE);
	}
	else
	{
		wait(&status);
		close_fds(o->pipes->fd_in, o->pipes->fd_out, o->pipes->fd_re_out);
	}
}

void	exe_single_command(t_obj *o)
{
	char	*command;

	if (check_pipe_redirects(o->pipes))
		fake_exe(o);
	else
	{
		command = find_command(o->pipes->arg);
		if (!command)
		{
			close_fds(o->pipes->fd_in, o->pipes->fd_out, o->pipes->fd_re_out);
			return ;
		}
		exe_fork(command, o);
	}
}