#include "minishell.h"

t_pipes	*pipes_new_node(t_link *link)
{
	t_pipes	*new;

	new = malloc(sizeof(t_pipes));
	if (!new)
		return (NULL);
	new->link = link;
	new->next = NULL;
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
		free_link(&(*pipes)->link);
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
