#include "../minishell.h"

char	*parse_spaces(char *input, int *index, t_obj *o)
{
	char	*command;
	int		i;

	(void )o;
	i = *index;
	command = ft_strdup(input);
	command[i++] = 0;
	printf("command %s\n", command);
	return (input);
}