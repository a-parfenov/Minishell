/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_out_redirect.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:44:29 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/13 20:51:53 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_write_file(char *file, t_obj *o)
{
	int		fd;
	char	*error;
	char	*tmp;

	file = build_file(file);
	if (!file)
		return (1);
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, S_IWRITE
			| S_IREAD | S_IRGRP | S_IROTH);
	if (fd == -1)
	{
		error = ft_strjoin(ERROR_NAME, ": ");
		tmp = error;
		error = ft_strjoin(error, file);
		perror(error);
		free_three_str(tmp, error, file);
		return (1);
	}
	free(file);
	o->fd_out = fd;
	o->is_redirect = 1;
	return (0);
}

char	*parse_out_redirect(char *input, int *index, t_obj *o)
{
	char	*start;
	char	*file;
	char	*end;
	int		i;
	int		j;

	i = (*index)--;
	start = ft_strdup(input);
	start[i++] = 0;
	pass_space_one(input, &i);
	if (check_len(input + i) || check_token(input[i]))
		return (free_two_str(start, input));
	j = i;
	pass_space_two(input, &i);
	end = ft_substr(input, i, ft_strlen(input));
	if (check_token_two(input[i]))
		return (free_three_str(start, input, end));
	start[i++] = 0;
	file = ft_strdup(start + j);
	if (open_write_file(file, o))
		return (free_three_str(start, input, end));
	file = input;
	input = ft_strjoin(start, end);
	free_three_str(file, start, end);
	return (input);
}
