#include "../minishell.h"

int	check_token(char c)
{
	if (c == '<')
	{
		printf("%s: %s\n", ERROR_NAME, IN_TOKEN);
		return (1);
	}
	else if (c == '>')
	{
		printf("%s: %s\n", ERROR_NAME, OUT_TOKEN);
		return (1);
	}
	else if (c == '|')
	{
		printf("%s: %s\n", ERROR_NAME, PIPE_TOKEN);
		return (1);
	}
	return (0);
}

int	check_token_two(char c)
{
	if (c == '<')
	{
		printf("%s: %s\n", ERROR_NAME, IN_TOKEN);
		return (1);
	}
	else if (c == '>')
	{
		printf("%s: %s\n", ERROR_NAME, OUT_TOKEN);
		return (1);
	}
	return (0);
}

int	check_len(char *s)
{
	if (ft_strlen(s) == 0)
	{
		printf("%s: %s\n", ERROR_NAME, NEW_TOKEN);
		return (1);
	}
	return (0);
}
