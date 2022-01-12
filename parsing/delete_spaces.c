/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_spaces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: teusebio <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 12:22:11 by teusebio          #+#    #+#             */
/*   Updated: 2022/01/10 12:22:13 by teusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*delete_front_spaces(char *input)
{
	int		i;
	int		size;
	char	*res;

	i = 0;
	size = ft_strlen(input);
	while (input[i] == ' ')
		i++;
	res = ft_substr(input, i, size);
	free(input);
	return (res);
}

char	*delete_end_spaces(char *input)
{
	int		size;
	char	*res;

	size = ft_strlen(input);
	while (size >= 0 && ft_strchr(" ", input[size]))
		size--;
	size++;
	input[size] = 0;
	res = ft_strdup(input);
	free(input);
	return (res);
}

char	*delete_spaces(char *input)
{
	input = delete_front_spaces(input);
	input = delete_end_spaces(input);
	return (input);
}
