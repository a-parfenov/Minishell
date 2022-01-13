#include "../minishell.h"

char	*parse_spaces(char *input, int *index, t_obj *o)
{
	char	*start;
	char	*end;
	int		i;

	i = *index;
	start = ft_strdup(input);
	start[i++] = 0;
	if (!o->link)
		o->link = link_new_node(start);
	else
		link_add_back(&o->link, link_new_node(start));
	pass_space_one(input, &i);
	end = ft_substr(input, i, ft_strlen(input));
	free(input);
	*index = -1;
	return (end);
}