/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:44:16 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/13 20:52:01 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	read_heredoc(char *limit, t_obj *o)
{
	char	*str;
	char	*tmp;
	char	*res;

	tmp = limit;
	limit = ft_strjoin(limit, "\n");
	free(tmp);
	res = ft_strdup("");
	write(1, "> ", 2);
	str = get_next_line(0);
	while (ft_strcmp(str, limit) != 0)
	{
		write(1, "> ", 2);
		tmp = res;
		res = ft_strjoin(res, str);
		free_two_str(tmp, str);
		str = get_next_line(0);
	}
	free(o->heredoc);
	o->heredoc = res;
	o->is_heredoc = 1;
	o->is_redirect++;
	put_str_to_link(ft_strdup(""), o);
	free_two_str(limit, str);
}

char	*parse_heredoc(char *input, int *index, t_obj *o)
{
	char	*start;
	char	*limit;
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
	limit = ft_strdup(start + j);
	read_heredoc(limit, o);
	limit = input;
	input = ft_strjoin(start, end);
	free_three_str(limit, start, end);
	return (input);
}
