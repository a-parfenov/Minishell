/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:29 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/24 11:20:34 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handler(int sig)
{
	(void)sig;
	rl_replace_line("", 0);
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

void	sig_handler(void)
{
	struct sigaction	sa;
	sigset_t			set;

	signal(SIGQUIT, SIG_IGN);
	sa.sa_handler = handler;
	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sa.sa_mask = set;
	sigaction(SIGINT, &sa, NULL);
}

int	main(int argc, char **argv, char **env)
{
	char	*input;
	t_obj	*o;

	(void)argv;
	(void)argc;
	g_exit = 0;
	o = init_o(env);
	if (!o)
		exit(EXIT_FAILURE);
	while (1)
	{
		sig_handler();
		input = readline(SHELL_NAME);
		if (!input)
		{
			ft_putstr_fd("\e[1A\e[12C" "\bexit\n", 1);
			break ;
		}
		if (ft_strlen(input) != 0)
			add_history(input);
		parse(input, o);
	}
	free_env_struct(o);
	free(o->heredoc);
	free(o);
}
