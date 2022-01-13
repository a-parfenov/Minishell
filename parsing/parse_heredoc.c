/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:44:16 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/13 11:44:19 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	read_heredoc(char *limit, t_obj *o)
{
	char	*str;
	char	*tmp;
	char	*res;

	tmp = limit;
	limit = ft_strjoin(limit, "\n");
	free(tmp);
	res = ft_strdup("");
	str = get_next_line(0);
	while (ft_strcmp(str, limit) != 0)
	{
		tmp = res;
		res = ft_strjoin(res, str);
		free_two_str(tmp, str);
		str = get_next_line(0);
	}
	free_arr(o->heredoc);
	o->heredoc = ft_split(res, '\0');
	if (!o->heredoc)
		return (1);
	o->is_heredoc = 1;
	free_three_str(limit, str, res);
	int i = 0;
	while (o->heredoc[i])
	{
		printf("%s", o->heredoc[i]);
		i++;
	}
	return (0);
}

char	*parse_heredoc(char *input, int *index, t_obj *o)
{
	char	*start;
	char	*limit;
	char	*end;
	int		i;
	int		j;

	i = (*index)--;
	start = ft_strdup(input);
	start[i++] = 0;
	i++;
	pass_space_one(input, &i);
	if (check_len(input + i) || check_token(input[i]))
		return (free_two_str(start, input));
	j = i;
	pass_space_two(input, &i);
	end = ft_substr(input, i, ft_strlen(input));
	start[i++] = 0;
	limit = ft_strdup(start + j);
	if (read_heredoc(limit, o))
		return (free_three_str(start, input, end));
	limit = input;
	input = ft_strjoin(start, end);
	free_three_str(limit, start, end);
	return (input);
}
