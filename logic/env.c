/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 20:31:12 by aleslie           #+#    #+#             */
/*   Updated: 2022/02/03 15:46:26 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	pwd_check(t_env	*tmp, t_obj	*o)
{
	// char	*way;
	char	*adr;
	char	*adr_check;

	if (ft_strncmp(tmp->env_str, "PWD=", 4) == 0)
	{
		adr_check = get_address();
		if (!adr_check)
			return ;
		printf("\n   %s\n", adr_check);
		adr = tmp->env_str + 4;
		printf("   %s\n\n", adr);
		if (ft_strncmp(adr_check, adr, ft_strlen(adr_check)) != 0)
		{
			// mercury_repl_env(o, "OLDPWD=", adr, 7);
			mercury_repl_env(o, "PWD=", adr_check, 4);
		}
		free(adr_check);
	}
}

void	command_env(t_obj	*o)
{
	t_env	*tmp;
	int		fd;

	fd = init_logic_fd(o);
	tmp = o->env_st;
	while (tmp != NULL)
	{
		pwd_check(tmp, o);
		ft_putendl_fd(tmp->env_str, fd);
		tmp = tmp->next;
	}
	close_fds(o->pipes->fd_in, o->pipes->fd_out, o->pipes->fd_re_out);
	g_exit = 0;
	// write(1, "\n", 1);
	// write(1, "\n", 1);
}
