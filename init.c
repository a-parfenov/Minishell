
#include "minishell.h"

t_obj	*init_o(char **env)
{
	t_obj	*o;

	o = malloc(sizeof(t_obj));
	if (!o)
		return (NULL);
	o->env = env;
	o->heredoc = NULL;
	o->fd_in = 0;
	o->fd_out = 1;
	o->fd_re_out = 1;
	o->is_heredoc = 0;
	o->is_redirect = 0;
	return (o);
}
