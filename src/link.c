/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:24 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/13 20:51:04 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_link	*link_new_node(char *str)
{
	t_link	*new;

	new = malloc(sizeof(t_link));
	if (!new)
		return (NULL);
	new->str = str;
	new->next = NULL;
	return (new);
}

void	link_add_back(t_link **link, t_link *new)
{
	t_link	*head;

	head = *link;
	if (head && new)
	{
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

void	free_link(t_link **link)
{
	t_link	*tmp;

	while (*link)
	{
		tmp = *link;
		*link = (*link)->next;
		free(tmp);
	}
}

int	link_size(t_link *link)
{
	int		count;

	count = 0;
	while (link)
	{
		count++;
		link = link->next;
	}
	return (count);
}
