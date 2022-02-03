#include "../include/minishell.h"

void	micro_print_err(char *command)
{
	char	*err;

	err = build_error_str(command);
	write(2, err, ft_strlen(err));
	write(2, ": ", 2);
	write(2, COMMAND_TOKEN, ft_strlen(COMMAND_TOKEN));
	write(2, "\n", 1);
	free_two_str(command, err);
}

char	*find_command(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (ft_strlen(arg[i]) != 0)
			return (ft_strdup(arg[i]));
		i++;
	}
	return (NULL);
}

char	*search_in_arr(char **arr, char *command)
{
	char	*full_path;
	char	*path;
	int		i;

	i = 0;
	while (arr[i])
	{
		path = ft_strjoin(arr[i], "/");
		full_path = ft_strjoin(path, command);
		free(path);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		i++;
	}
	full_path = ft_strdup(command);
	free(command);
	return (full_path);
}

char	*find_command_in_env(char *command, t_obj *o)
{
	char	*env;
	char	*full_path;
	char	**arr;

	if (get_variable_env(o, &env, "PATH=", 5))
		return (NULL);
	arr = ft_split(env, ':');
	if (!arr)
		return (NULL);
	full_path = search_in_arr(arr, command);
	free_arr(arr);
	return (full_path);
}

void	exe_heredoc(t_pipes *pipes)
{
	int		pipe_fd[2];

	if (pipe(pipe_fd) == -1)
	{
		perror(ERROR_NAME);
		exit(EXIT_FAILURE);
	}
	write(pipe_fd[1], pipes->heredoc, ft_strlen(pipes->heredoc));
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
}
