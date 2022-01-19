#include "../include/minishell.h"

void	micro_print_err(char *command)
{
	char	*err;

	err = build_error_str(command);
	printf("%s: %s\n", err, COMMAND_TOKEN);
	free(err);
	g_exit = 1;
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

char	*find_command_in_env(char *command)
{
	char	*env;
	char	*full_path;
	char	**arr;

	env = getenv("PATH");
	if (!env)
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

	pipe(pipe_fd);
	write(pipe_fd[1], pipes->heredoc, ft_strlen(pipes->heredoc));
	close(pipe_fd[1]);
	pipes->fd_in = pipe_fd[0];
}
