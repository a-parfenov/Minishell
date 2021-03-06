/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:00:24 by teusebio          #+#    #+#             */
/*   Updated: 2022/01/13 20:51:45 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_unclosed(char *start, int i, char *input)
{
	if (start[i] == 0)
	{
		printf("%s: %s\n", ERROR_NAME, ONE_TOKEN);
		free_two_str(start, input);
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

char	*init_q_start(int *i, int *index, char *input)
{
	char	*start;

	*i = *index;
	start = ft_strdup(input);
	start[(*i)++] = 0;
	while (start[*i] && start[*i] != '\'')
		(*i)++;
	if (check_unclosed(start, *i, input))
		return (NULL);
	start[(*i)++] = 0;
	return (start);
}

char	*parse_quote(char *input, int *index)
{
	char	*start;
	char	*mid;
	char	*end;
	char	*res;
	int		i;

	start = init_q_start(&i, index, input);
	if (!start)
		return (NULL);
	mid = ft_strdup(start + *index + 1);
	res = helper(start, mid);
	*index = ft_strlen(res) - 1;
	start = res;
	end = ft_substr(input, i, ft_strlen(input));
	res = ft_strjoin(res, end);
	free_three_str(input, start, end);
	return (res);
}
