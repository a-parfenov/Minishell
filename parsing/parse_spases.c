#include "../minishell.h"

char	*parse_spaces(char *input, int *index, t_obj *o)
{
	char	*start;
	char	*end;
	int		i;

	i = *index;
	start = ft_strdup(input);
	start[i++] = 0;
	put_str_to_link(start, o);
	pass_space_one(input, &i);
	end = ft_substr(input, i, ft_strlen(input));
	free(input);
	*index = -1;
	return (end);
}