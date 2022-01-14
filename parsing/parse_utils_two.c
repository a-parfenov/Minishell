/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_two.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:44:53 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/13 20:51:31 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	int		i;
	int		size;
	char	**arg;

	size = link_size(o->link);
	printf("size link = %d\n", size);
	arg = malloc(sizeof(char *) * size + 1);
	if (!arg)
		return ;
	i = 0;
	while (o->link)
	{
		arg[i] = o->link->str;
		o->link = o->link->next;
		i++;
	}
	arg[i] = NULL;
	if (!o->pipes)
		o->pipes = pipes_new_node(arg);
	else
		pipes_add_back(&o->pipes, pipes_new_node(arg));
	free_link(&o->link);
	o->link = NULL;
}
