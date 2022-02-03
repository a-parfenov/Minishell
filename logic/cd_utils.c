/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 21:06:21 by aleslie           #+#    #+#             */
/*   Updated: 2022/02/03 16:04:59 by aleslie          ###   ########.fr       */
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

	pwd_check(o->env_st, o);
	get_variable_env(o, &way, "PWD=", 4);
	buf = get_address();
	if (!buf)
		buf = ft_strdup(way);
	last = ft_strrchr(buf, '/');
	prev = ft_substr(buf, 0, ft_strlen(buf) - ft_strlen(last));
	if (!prev)
		print_error("func back", "cd");
	chdir(prev);
	get_variable_env(o, &way, "PWD=", 4);
	mercury_repl_env(o, "OLDPWD=", way, 7);
	if (count_s(way, D) == 1)
		mercury_repl_env(o, "PWD=", D, 4);
	else
		mercury_repl_env(o, "PWD=", prev, 4);
	free(buf);
	free(prev);
}

int	ft_cd_prev(t_obj *o)
{
	char *way;
	char *way_old;
	
	if (get_variable_env(o, &way_old, "OLDPWD=", 7))
	{
		ft_putendl_fd("minishell: cd: OLDPWD not set", 1);
		return (1);
	}
	if (chdir(way_old))
	{
		do_chdir(way_old);
		return (1);
	}
	get_variable_env(o, &way, "PWD=", 4);
	get_variable_env(o, &way_old, "OLDPWD=", 7);
	printf("\nway   %s\n", way);
	printf("\nold   %s\n", way_old);
	mercury_repl_env(o, "OLDPWD=", way, 7);
	mercury_repl_env(o, "PWD=", way_old, 4);
	return (0);
}