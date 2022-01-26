/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 23:03:56 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/26 12:48:14 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	command_pwd(t_obj *o)
{
	while (o->env_st != NULL)
	{
		if (ft_strncmp(o->env_st->env_str, "PWD=", 4) == 0)
		{
			ft_putendl_fd(o->env_st->env_str + 4, o->pipes->fd_in);
			break;
		}
		o->env_st = o->env_st->next;
	}
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
