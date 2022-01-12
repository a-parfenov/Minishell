
#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	if (arr)
	{
		i = 0;
		while (arr[i])
			free(arr[i++]);
		free(arr);
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] == s2[i] && s1[i] && s2[i])
			i++;
		return (s1[i] - s2[i]);
	}
	return (1);
}
