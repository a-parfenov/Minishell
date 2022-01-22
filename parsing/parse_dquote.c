/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dquote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:06:25 by teusebio          #+#    #+#             */
/*   Updated: 2022/01/13 20:52:05 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_unclosed(char *start, int i, char *input)
{
	if (start[i] == 0)
	{
		printf("%s: %s\n", ERROR_NAME, TWO_TOKEN);
		free_two_str(input, start);
		return (1);
	}
	return (0);
}

static char	*helper(char *start, char *mid)
{
	char	*res;

	res = ft_strjoin(start, mid);
	free_two_str(start, mid);
	return (res);
}

char	*init_dq_start(int *i, int *index, char *input)
{
	char	*start;

	*i = *index;
	start = ft_strdup(input);
	start[(*i)++] = 0;
	while (start[*i] && start[*i] != '"')
		(*i)++;
	if (check_unclosed(start, *i, input))
		return (NULL);
	start[(*i)++] = 0;
	return (start);
}

char	*parse_dquote(char *input, int *index, t_obj *o)
{
	char	*start;
	char	*mid;
	char	*end;
	char	*res;
	int		i;

	start = init_dq_start(&i, index, input);
	if (!start)
		return (NULL);
	mid = ft_strdup(start + *index + 1);
	if (ft_strchr(mid, '$'))
		mid = find_dollar(mid, o);
	res = helper(start, mid);
	*index = ft_strlen(res) - 1;
	start = res;
	end = ft_substr(input, i, ft_strlen(input));
	res = ft_strjoin(res, end);
	if (ft_strlen(res) == 0)
		put_str_to_link(ft_strdup(""), o);
	free_three_str(input, start, end);
	return (res);
}
