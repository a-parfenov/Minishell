#include "../include/minishell.h"

int	check_pipe_token(char *input, t_obj *o)
{
	if (!o->link && !o->is_redirect && !o->is_heredoc)
	{
		printf("%s: %s\n", ERROR_NAME, PIPE_TOKEN);
		free(input);
		return (1);
	}
	return (0);
}

int	check_p_token(char *input, int i)
{
	if (input[i] == '|')
	{
		printf("%s: %s\n", ERROR_NAME, PIPE_TOKEN);
		free(input);
		return (1);
	}
	return (0);
}

int	check_unclosed_pipe(char *input, char *end)
{
	if (ft_strlen(end) == 0)
	{
		printf("%s: %s\n", ERROR_NAME, THREE_TOKEN);
		free_two_str(input, end);
		return (1);
	}
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
	if (ft_strlen(str) != 0)
		put_str_to_link(str, o);
	else
		free(str);
	if (check_pipe_token(input, o))
		return (NULL);
	put_link_to_pipe(o);
	pass_space_one(input, &i);
	if (check_p_token(input, i))
		return (NULL);
	end = ft_substr(input, i, ft_strlen(input));
	if (check_unclosed_pipe(input, end))
		return (NULL);
	*index = -1;
	free(input);
	return (end);
}