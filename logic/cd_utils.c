/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:06:21 by aleslie           #+#    #+#             */
/*   Updated: 2022/02/02 21:09:13 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	count_s(char *way, char	*d)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (way[++i])
	{
		if (way[i] == d[0])
			j++;
	}
	return (j);
}

void	cd_back(t_obj *o)
{
	char	*way;
	char	*buf;
	char	*last;
	char	*prev;
	char	d[2];

	d[0] = '/';
	d[1] = '\0';
	get_variable_env(o, &way, "PWD=", 4);
	buf = get_address();
	if (!buf)
		buf = way;
	last = ft_strrchr(buf, '/');
	prev = ft_substr(buf, 0, ft_strlen(buf) - ft_strlen(last));
	if (!prev)
		print_error("func back", "cd");
	chdir(prev);
	get_variable_env(o, &way, "PWD=", 4);
	mercury_repl_env(o, "OLDPWD=", way, 7);
	if (count_s(way, d) == 1)
		mercury_repl_env(o, "PWD=", d, 4);
	else
		mercury_repl_env(o, "PWD=", prev, 4);
}
