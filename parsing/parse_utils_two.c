#include "../minishell.h"

int	check_token(char c)
{
	if (c == '<')
	{
		printf("%s: %s\n", ERROR_NAME, IN_TOKEN);
		return (1);
	}
	else if (c == '>')
	{
		printf("%s: %s\n", ERROR_NAME, OUT_TOKEN);
		return (1);
	}
	else if (c == '|')
	{
		printf("%s: %s\n", ERROR_NAME, PIPE_TOKEN);
		return (1);
	}
	return (0);
}

int	check_token_two(char c)
{
	if (c == '<')
	{
		printf("%s: %s\n", ERROR_NAME, IN_TOKEN);
		return (1);
	}
	else if (c == '>')
	{
		printf("%s: %s\n", ERROR_NAME, OUT_TOKEN);
		return (1);
	}
	return (0);
}

int	check_len(char *s)
{
	if (ft_strlen(s) == 0)
	{
		printf("%s: %s\n", ERROR_NAME, NEW_TOKEN);
		return (1);
	}
	return (0);
}

void	put_str_to_link(char *str, t_obj *o)
{
	if (!o->link)
		o->link = link_new_node(str);
	else
		link_add_back(&o->link, link_new_node(str));
}

void	put_link_to_pipe(t_obj *o)
{
	if (!o->pipes)
		o->pipes = pipes_new_node(o->link);
	else
		pipes_add_back(&o->pipes, pipes_new_node(o->link));
	o->link = NULL;
}