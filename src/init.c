/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:18 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/13 22:47:16 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_obj	*init_o(char **env)
{
	t_obj	*o;

	o = malloc(sizeof(t_obj));
	if (!o)
		return (NULL);
	o->env = env;
	o->heredoc = NULL;
	o->fd_in = 0;
	o->fd_out = 1;
	o->fd_re_out = 1;
	o->is_heredoc = 0;
	o->is_redirect = 0;
	o->pipes = NULL;
	o->link = NULL;
	return (o);
}
