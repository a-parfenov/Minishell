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

static char	*init_dollar(char *start, int i)
{
	char	*dollar;
	char	*val;

	dollar = ft_strdup(start + i + 1);
	val = getenv(dollar);
	free(dollar);
	if (val)
		val = ft_strdup(val);
	else
		val = ft_strdup("");
	return (val);
}

char	*parse_dollar(char *mid, int *index)
{
	char	*res;
	char	*start;
	char	*end;
	char	*dollar;
	int		i;

	i = *index;
	start = ft_strdup(mid);
	start[i++] = 0;
	while (ft_isalpha(start[i]) || start[i] == '_')
		i++;
	start[i] = 0;
	dollar = init_dollar(start, *index);
	res = ft_strjoin(start, dollar);
	free_two_str(start, dollar);
	*index = ft_strlen(res) - 1;
	start = mid;
	end = ft_substr(mid, i, ft_strlen(mid));
	mid = ft_strjoin(res, end);
	free_three_str(start, res, end);
	return (mid);
}

char	*find_dollar(char *mid)
{
	int	i;

	i = 0;
	while (mid[i])
	{
		if (mid[i] == '$' && mid[i + 1] != '$'
			&& mid[i + 1] != ' ' && mid[i + 1] != 0)
			mid = parse_dollar(mid, &i);
		i++;
	}
	return (mid);
}
