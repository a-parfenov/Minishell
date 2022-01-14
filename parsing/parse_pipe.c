#include "minishell.h"

int	check_pipe_token(char *str, char *input, t_obj *o)
{
	if (ft_strlen(str) == 0 && !o->link
		&& (!o->is_redirect && !o->is_heredoc))
	{
		printf("%s: %s\n", ERROR_NAME, PIPE_TOKEN);
		free_two_str(input, str);
		return (1);
	}
	return (0);
}

int	check_size(char *str, char *input, t_obj *o)
{
	if (ft_strlen(str) != 0)
	{
		if (check_pipe_token(str, input, o))
			return (1);
		put_str_to_link(str, o);
	}
	else
		free(str);
	return (0);
}

char	*parse_pipe(char *input, int *index, t_obj *o)
{
	char	*str;
	char	*end;
	int		i;

	i = *index;
	str = ft_strdup(input);
	str[i++] = 0;
	if (check_size(str, input, o))
		return (NULL);
	put_link_to_pipe(o);
	pass_space_one(input, &i);
	if (input[i] == '|')
	{
		printf("%s: %s\n", ERROR_NAME, PIPE_TOKEN);
		free(input);
		return (NULL);
	}
	end = ft_substr(input, i, ft_strlen(input));
	if (ft_strlen(end) == 0)
		printf("dfghj\n");
	*index = -1;
	free(input);
	return (end);
}