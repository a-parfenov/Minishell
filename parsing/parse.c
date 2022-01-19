/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:04 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/17 10:36:00 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_env_struct(t_obj *o)
{
	t_env *begin;

	while (o->env_st)
	{
		free(o->env_st->env_str);
		begin = o->env_st;
		o->env_st = o->env_st->next;
		free(begin);
	}
}

void	free_o(t_obj *o)
{
	free_pipes(&o->pipes);
	free(o->heredoc);
	// free_env_struct(o);
	// free(o);
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
			input = parse_dquote(input, &i, o);
		else if (input[i] == '$'
			&& (ft_isalnum(input[i + 1]) || input[i + 1] == '?'))
			input = parse_dollar(input, &i, o);
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
	t_pipes	*tmp;

	if (input[0] == 0)
	{
		free(input);
		// free(o);
		return ;
	}
	input = delete_spaces(input);
	input = combine(input, o);
	if (!input)
	{
		free_o(o);
		return ;
	}
	tmp = o->pipes;
	exe(o);
	o->pipes = tmp;
	free_o(o);
}
