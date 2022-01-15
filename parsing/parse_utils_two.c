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

char	*build_error_str(char *file)
{
	char	*error;
	char	*tmp;

	error = ft_strjoin(ERROR_NAME, ": ");
	tmp = error;
	error = ft_strjoin(error, file);
	free(tmp);
	return (error);
}
