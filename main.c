
#include "minishell.h"

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
