/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:04 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/14 10:33:23 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		else if (input[i] == '$'
			&& (ft_isalnum(input[i + 1]) || input[i + 1] == '?'))
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
	// printf("input start = %s\n", input);
	input = delete_spaces(input);
	input = combine(input, o);
	if (!input)
	{
		printf("pipes size %d\n", pipes_size(o->pipes));
		free_o(o);
		return ;
	}
	printf("pipes size %d\n", pipes_size(o->pipes));
//	while (o->pipes)
//	{
//		int i = 0;
//		while (o->pipes->arg[i])
//		{
//			printf("arg = %s\n", o->pipes->arg[i]);
//			i++;
//		}
//		printf("flag heredoc = %d\n", o->pipes->is_heredoc);
//		printf("flag redirect = %d\n", o->pipes->is_redirect);
//		printf("flag in = %d\n", o->pipes->fd_in);
//		printf("flag out = %d\n", o->pipes->fd_out);
//		printf("flag re_out = %d\n", o->pipes->fd_re_out);
//		o->pipes = o->pipes->next;
//	}
	printf("input end = %s\n", input);
//		exe(o);
	free_o(o);
}
