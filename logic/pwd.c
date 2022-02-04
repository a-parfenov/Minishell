/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 23:03:56 by aleslie           #+#    #+#             */
/*   Updated: 2022/02/04 11:09:00 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	print_pwd(int fd)
{
	char	*way;

	way = NULL;
	ft_putendl_fd(init_way(way), fd);
	free(way);
}

void	command_pwd(t_obj *o)
{
	int		fd;
	int		flag;
	t_env	*tmp;

	fd = init_logic_fd(o);
	tmp = o->env_st;
	flag = 1;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->env_str, "PWD=", 4) == 0)
		{
			ft_putendl_fd(tmp->env_str + 4, fd);
			flag = 0;
			break ;
		}
		tmp = tmp->next;
	}
	if (flag)
		print_pwd(fd);
	else
		g_exit = 0;
	close_fds(o->pipes->fd_in, o->pipes->fd_out, o->pipes->fd_re_out);
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
