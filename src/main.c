/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:29 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/13 12:08:27 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **env)
{
	char				*input;
	t_obj				*o;

	(void)argv;
	(void)argc;
	while (1)
	{
		input = readline(SHELL_NAME);
		if (!input)
			break;
		if (ft_strlen(input) != 0)
			add_history(input);
		o = init_o(env);
		if (!o)
			exit(EXIT_FAILURE);
		parse(input, o);
	}
}
