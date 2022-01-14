/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:34:28 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/14 18:44:57 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_variable_env(t_obj *o, char **adr, char *key_word, int n)
{
	int		i;

	i = -1;
	while (o->env[++i])
	{
		if (ft_strncmp(o->env[i], key_word, n) == 0)
		{
			*adr = o->env[i] + n;
			return (0);
		}
	}
	return (1);
}

void	command_cd(t_obj *o)
{
	char	*home;

	// if (!o->pipes->arg || o->pipes->arg[0])
		
	if (get_variable_env(o, &home, "HOME=", 5))
	{
		ft_putendl_fd("Error cd: HOME not set", 1);
		return ;
	}
	printf("|| %s\n", home);
	// printf("|| %s\n", home);
	// (o->pipes->arg[1] + 1 == '\0' && ft_strncmp(o->pipes->arg[1], ".", 1))
	if (!o->pipes->arg[1])
	{
		chdir(home);
		printf("|---|\n");
		
	}	
	// printf("|| %s\n", o->pipes->arg[1] + 1);
	return ;
}