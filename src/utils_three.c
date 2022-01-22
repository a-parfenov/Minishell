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
