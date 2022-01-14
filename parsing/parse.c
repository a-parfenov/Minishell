
#include "../include/minishell.h"

void	free_o(t_obj *o)
{
	free_pipes(&o->pipes);
	free_arr(o->heredoc);
	free(o);
}

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
	put_str_to_link(input, o);
	put_link_to_pipe(o);
	return (input);
}

void	parse(char *input, t_obj *o)
{
	if (input[0] == 0)
	{
		free(input);
		free(o);
		return ;
	}
	printf("input start = %s\n", input);
	input = delete_spaces(input);
	input = combine(input, o);
	if (!input)
	{
		printf("%d\n", pipes_size(o->pipes));
		if (!o->pipes)
			free_link(&o->link);
		free_o(o);
		return ;
	}
	printf("%d\n", pipes_size(o->pipes));
//	while (o->pipes)
//	{
//		int i = 0;
//		while (o->pipes->arg[i])
//		{
//			printf("arg = %s\n", o->pipes->arg[i]);
//			i++;
//		}
//		o->pipes = o->pipes->next;
//	}
	printf("input end = %s\n", input);
//		exe(o);
	free_o(o);
}
