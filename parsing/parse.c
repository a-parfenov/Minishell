/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:04 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/13 11:45:05 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	if (!o->link)
		o->link = link_new_node(input);
	else
		link_add_back(&o->link, link_new_node(input));
	return (input);
}

void	parse(char *input, t_obj *o)
{
	printf("input start %s\n", input);
	input = delete_spaces(input);
	input = combine(input, o);
	if (!input)
	{
		free_arr(o->heredoc);
		free(o);
		return ;
	}
	while (o->link)
	{
		printf("%s\n", o->link->str);
		o->link = o->link->next;
	}
	printf("input end %s\n", input);
//		exe(o);
	free_arr(o->heredoc);
	free(input);
	free(o);
}
