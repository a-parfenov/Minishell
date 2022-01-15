#include "../include/minishell.h"

char	**put_link_to_arg(int size, t_obj *o)
{
	int		i;
	char	**res;

	res = malloc(sizeof(char *) * size + 1);
	if (!res)
		return (NULL);
	i = 0;
	while (o->link)
	{
		res[i] = o->link->str;
		o->link = o->link->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}

void	put_link_to_pipe(t_obj *o)
{
	t_link	*tmp;
	int		size;
	char	**arg;

	size = link_size(o->link);
	printf("size link = %d\n", size);
	tmp = o->link;
	arg = put_link_to_arg(size, o);
	if (!o->pipes)
		o->pipes = pipes_new_node(arg, o);
	else
		pipes_add_back(&o->pipes, pipes_new_node(arg, o));
	re_init_o_fd(o);
	free_link(&tmp);
	o->link = NULL;
}
