/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:34 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/13 20:50:58 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_pipes	*pipes_new_node(char **arg, t_obj *o)
{
	t_pipes	*new;

	new = malloc(sizeof(t_pipes));
	if (!new)
		return (NULL);
	new->arg = arg;
	new->next = NULL;
	new->fd_in = o->fd_in;
	new->fd_out = o->fd_out;
	new->fd_re_out = o->fd_re_out;
	new->is_heredoc = o->is_heredoc;
	new->is_redirect = o->is_redirect;
	return (new);
}

void	pipes_add_back(t_pipes **pipes, t_pipes *new)
{
	t_pipes	*head;

	head = *pipes;
	if (head && new)
	{
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

void	free_pipes(t_pipes **pipes)
{
	t_pipes	*tmp;

	while (*pipes)
	{
		printf("%p\n", pipes);
		free_arr((*pipes)->arg);
		tmp = *pipes;
		*pipes = (*pipes)->next;
		free(tmp);
	}
}

int	pipes_size(t_pipes *pipes)
{
	int		count;

	count = 0;
	while (pipes)
	{
		count++;
		pipes = pipes->next;
	}
	return (count);
}
