#include "../minishell.h"

char	*parse_pipe(char *input, int *index, t_obj *o)
{
	char	*command;
	char	*end;
	int		i;

	(void )o;
	i = *index;
	command = ft_strdup(input);
	command[i++] = 0;
	if (ft_strlen(command) == 0 && (!o->is_redirect && !o->is_heredoc))
	{
		printf("%s: %s\n", ERROR_NAME, PIPE_TOKEN);
		free(command);
		free(input);
		return (NULL);
	}
	end = ft_substr(input, i, ft_strlen(input));
	*index = 0;
	printf("end %s\n", end);
	printf("command %s\n", command);
	free(command);
	free(input);
	return (end);
}