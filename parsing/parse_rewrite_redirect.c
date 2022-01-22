/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rewrite_redirect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:44:42 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/13 20:51:41 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	open_rewrite_file(char *file, t_obj *o)
{
	int		fd;
	char	*error;

	file = build_file(file, o);
	if (!file)
		return (1);
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, S_IWRITE
			| S_IREAD | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		error = build_error_str(file);
		perror(error);
		free_two_str(error, file);
		g_exit = 1;
		return (1);
	}
	free(file);
	close(o->fd_re_out);
	o->fd_re_out = fd;
	o->is_redirect++;
	put_str_to_link(ft_strdup(""), o);
	return (0);
}

char	*init_rewrite_start(int *i, int *index, char *input)
{
	char	*start;

	*i = (*index)--;
	start = ft_strdup(input);
	start[(*i)++] = 0;
	(*i)++;
	pass_space_one(input, i);
	return (start);
}

char	*parse_rewrite_redirect(char *input, int *index, t_obj *o)
{
	char	*start;
	char	*file;
	char	*end;
	int		i;
	int		j;

	start = init_rewrite_start(&i, index, input);
	if (check_len(input + i) || check_token(input[i]))
		return (free_two_str(start, input));
	j = i;
	pass_space_two(input, &i);
	end = ft_substr(input, i, ft_strlen(input));
	end = delete_spaces(end);
	start[i++] = 0;
	file = ft_strdup(start + j);
	if (open_rewrite_file(file, o))
		return (free_three_str(start, input, end));
	file = input;
	input = ft_strjoin(start, end);
	free_three_str(file, start, end);
	return (input);
}
