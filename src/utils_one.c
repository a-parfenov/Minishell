/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 11:45:39 by aleslie           #+#    #+#             */
/*   Updated: 2022/02/03 17:48:02 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	print_error(char *error, char *str)
{
	ft_putstr_fd("\033[0;36m\033[1mminishell ▸ \033[0m", 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(error, 2);
	g_exit = 1;
}

void	close_fds(int fd1, int fd2, int fd3)
{
	close(fd1);
	close(fd2);
	close(fd3);
}

void	init_fds(int fd_in, int fd_out, int fd_re_out)
{
	if (fd_in != -1)
		dup2(fd_in, STDIN_FILENO);
	if (fd_re_out != -1)
		dup2(fd_re_out, STDOUT_FILENO);
	if (fd_out != -1)
		dup2(fd_out, STDOUT_FILENO);
}
