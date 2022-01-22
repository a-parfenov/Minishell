#include "../include/minishell.h"

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

void	child(char *command, t_obj *o, int fd_in, int fd_out)
{
	char	**argv;

	argv = re_build_argv(o->pipes->arg);
	if (o->pipes->is_heredoc)
		exe_heredoc(o->pipes);
	if (o->is_pipe)
		init_pipe_fds(fd_in, fd_out, o);
	init_fds(o->pipes->fd_in, o->pipes->fd_out, o->pipes->fd_re_out);
	execve(argv[0], argv, o->env);
	micro_print_err(command);
	free_arr(argv);
	exit(EXIT_FAILURE);
}

void	parent(pid_t pid, t_obj *o, int pipe_in, int pipe_out)
{
	int		status;

	if (o->is_pipe)
	{
		close(pipe_out);
		dup2(pipe_in, o->tmp_in);
	}
	waitpid(pid, &status, 0);
	g_exit = WEXITSTATUS(status);
	printf("exit code %d\n", g_exit);
	close_fds(o->pipes->fd_in, o->pipes->fd_out, o->pipes->fd_re_out);
	close(pipe_in);
	close(pipe_out);
}

void	exe_fork(char *command, t_obj *o)
{
	pid_t	pid;
	int		pipe_fd[2];

	if (o->is_pipe)
	{
		if (pipe(pipe_fd) < 0)
		{
			perror(ERROR_NAME);
			return;
		}
//		printf("pipe_fd 0 %d\n", pipe_fd[0]);
//		printf("pipe_fd 1 %d\n", pipe_fd[1]);
	}
	pid = fork();
	if (pid < 0)
	{
		perror(ERROR_NAME);
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
		child(command, o, pipe_fd[0], pipe_fd[1]);
	else
		parent(pid, o, pipe_fd[0], pipe_fd[1]);
}

void	exe_command(t_obj *o)
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
