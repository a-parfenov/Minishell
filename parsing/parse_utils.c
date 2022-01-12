#include "../minishell.h"

char	*free_two_str(char *s1, char *s2)
{
	free(s1);
	free(s2);
	return (NULL);
}

char	*free_three_str(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
	return (NULL);
}

void	pass_space_one(char *input, int *i)
{
	while (input[*i] == ' ')
		(*i)++;
}

void	pass_space_two(char *input, int *i)
{
	while (input[*i] && input[*i] != ' '
		&& input[*i] != '<' && input[*i] != '>' && input[*i] != '|')
		(*i)++;
}

char	*build_file(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (file[i] == '\'')
			file = parse_quote(file, &i);
		else if (file[i] == '"')
			file = parse_dquote(file, &i);
		else if (file[i] == '$')
			file = parse_dollar(file, &i);
		if (!file)
			return (NULL);
		i++;
	}
	return (file);
}
