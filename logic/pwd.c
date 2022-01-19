/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 23:03:56 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/18 16:44:35 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	command_pwd(t_obj *o)
{
	// int	i;

	// i = -1;
	// while (o->env[++i])
	// {
	// 	if (ft_strncmp(o->env[i], "PWD=", 4) == 0)
	// 	{
	// 		ft_putstr_fd(o->env[i] + 4, 1);
	// 		ft_putstr_fd("\n", 1);
	// 		return ;
	// 	}
	// }
	// ft_putendl_fd(o->pwd, 1);
	while (o->env_st != NULL)
	{
		if (ft_strncmp(o->env_st->env_str, "PWD=", 4) == 0)
		{
			ft_putendl_fd(o->env_st->env_str + 4, 1);
			break;
		}
		o->env_st = o->env_st->next;
	}
	// mercury_repl_env(o, "_=", "pwd", 3);
}

char	*get_address(void)
{
	char	*buf;
	char	*copy;

	buf = malloc(sizeof(char) * 1000);
	copy = buf;
	if (!buf)
		print_error("malloc, get address", "cd");
	buf = getcwd(buf, 1000);
	if (!buf)
	{
		free(copy);
		
		return (NULL);
	}
	return (buf);
}
