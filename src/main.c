/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:29 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/17 10:32:03 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **env)
{
	char				*input;
	t_obj				*o;

	(void)argv;
	(void)argc;
	g_exit = 0;
	o = init_o(env);
	if (!o)
		exit(EXIT_FAILURE);
	while (1)
	{
		input = readline(SHELL_NAME);
		if (!input)
			break;
		if (ft_strlen(input) != 0)
			add_history(input);
		parse(input, o);
	}
	free_env_struct(o);
	free(o);
}
