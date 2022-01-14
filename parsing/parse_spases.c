/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_spases.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:44:46 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/13 20:51:36 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*parse_spaces(char *input, int *index, t_obj *o)
{
	char	*start;
	char	*end;
	int		i;

	i = *index;
	start = ft_strdup(input);
	start[i++] = 0;
	put_str_to_link(start, o);
	pass_space_one(input, &i);
	end = ft_substr(input, i, ft_strlen(input));
	free(input);
	*index = -1;
	return (end);
}
