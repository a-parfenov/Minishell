
#include "../minishell.h"

char	*redirects(char *input, int *i, t_obj *o)
{
	if (input[*i] == '<' && input[*i + 1] == '<')
		input = parse_heredoc(input, i, o);
	else if (input[*i] == '<')
		input = parse_in_redirect(input, i, o);
	else if (input[*i] == '>' && input[*i + 1] == '>')
		input = parse_rewrite_redirect(input, i, o);
	else if (input[*i] == '>')
		input = parse_out_redirect(input, i, o);
	return (input);
}

char	*combine(char *input, t_obj *o)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (input[i] == '\'')
			input = parse_quote(input, &i);
		else if (input[i] == '"')
			input = parse_dquote(input, &i);
		else if (input[i] == '$' && ft_isalpha(input[i + 1]))
			input = parse_dollar(input, &i);
		else if (input[i] == '<' || input[i] == '>')
			input = redirects(input, &i, o);
		else if (input[i] == '|')
			input = parse_pipe(input, &i, o);
		else if (input[i] == ' ')
			input = parse_spaces(input, &i, o);
		if (!input)
			return (NULL);
		i++;
	}
	return (input);
}

void	parse(char *input, t_obj *o)
{
//	int len = ft_strlen(input);
	printf("input start %s\n", input);
	input = delete_spaces(input);
	input = combine(input, o);
	if (!input)
	{
		free_arr(o->heredoc);
		free(o);
		return ;
	}
	printf("input end %s\n", input);
//	int i = 0;
//	while (i < len)
//	{
//		printf("%c\n", input[i]);
//		i++;
//	}
//		exe(o);
	free_arr(o->heredoc);
	free(input);
	free(o);
}
