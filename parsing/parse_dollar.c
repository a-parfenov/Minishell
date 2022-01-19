/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_dollar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:21:28 by teusebio          #+#    #+#             */
/*   Updated: 2022/01/13 20:52:09 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*init_dollar(char *start, int i, t_obj *o)
{
	char	*dollar;
	char	*val;

	dollar = ft_strdup(start + i + 1);
	val = getenv(dollar);
	free(dollar);
	if (val)
		val = ft_strdup(val);
	else
	{
		o->is_was_dollar++;
		val = ft_strdup("");
	}
	return (val);
}

char	*check_find_dollar(char *start, int *i, int index, t_obj *o)
{
	char	*dollar;

	if (start[*i] == '?')
	{
		dollar = ft_itoa(g_exit);
		(*i)++;
	}
	else
	{
		while (ft_isalnum(start[*i]) || start[*i] == '_')
			(*i)++;
		start[*i] = 0;
		dollar = init_dollar(start, index, o);
	}
	return (dollar);
}

char	*parse_dollar(char *mid, int *index, t_obj *o)
{
	char	*res;
	char	*start;
	char	*end;
	char	*dollar;
	int		i;

	i = *index;
	start = ft_strdup(mid);
	start[i++] = 0;
	dollar = check_find_dollar(start, &i, *index, o);
	res = ft_strjoin(start, dollar);
	free_two_str(start, dollar);
	*index = ft_strlen(res) - 1;
	start = mid;
	end = ft_substr(mid, i, ft_strlen(mid));
	mid = ft_strjoin(res, end);
	free_three_str(start, res, end);
	return (mid);
}

char	*find_dollar(char *mid, t_obj *o)
{
	int	i;

	i = 0;
	while (mid[i])
	{
		if (mid[i] == '$' && (ft_isalnum(mid[i + 1]) || mid[i + 1] == '?'))
			mid = parse_dollar(mid, &i, o);
		i++;
	}
	return (mid);
}
