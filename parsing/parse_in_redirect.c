#include "../include/minishell.h"

int	open_read_file(char *file, t_obj *o)
{
	int		fd;
	char	*error;

	file = build_file(file, o);
	if (!file)
		return (1);
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		error = build_error_str(file);
		perror(error);
		free_two_str(error, file);
		g_exit = 1;
		return (1);
	}
	free(file);
	close(o->fd_in);
	o->fd_in = fd;
	o->is_redirect++;
	return (0);
}

char	*parse_in_redirect(char *input, int *index, t_obj *o)
{
	char	*start;
	char	*file;
	char	*end;
	int		i;
	int		j;

	i = (*index)--;
	start = ft_strdup(input);
	start[i++] = 0;
	pass_space_one(input, &i);
	if (check_len(input + i) || check_token(input[i]))
		return (free_two_str(start, input));
	j = i;
	pass_space_two(input, &i);
	end = ft_substr(input, i, ft_strlen(input));
	if (check_token_two(input[i]))
		return (free_three_str(start, input, end));
	start[i++] = 0;
	file = ft_strdup(start + j);
	if (open_read_file(file, o))
		return (free_three_str(start, input, end));
	file = input;
	input = ft_strjoin(start, end);
	free_three_str(file, start, end);
	return (input);
}
