/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:34:28 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/17 17:00:47 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_variable_env(t_obj *o, char **adr, char *key_word, int n)
{
	t_env	*temp;

	temp = o->env_st;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->env_str, key_word, n) == 0)
		{
			*adr = temp->env_str + n;
			return (0);
		}
		temp = temp->next;
	}
	return (1);
}

void	mercury_repl_env(t_obj *o, char *str, char *way, int symb)
{
	t_env	*temp;

	temp = o->env_st;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->env_str, str, symb) == 0)
		{
			free(temp->env_str);
			temp->env_str = ft_strjoin(str, way);
			break;
		}
		temp = temp->next;
	}
}

int	do_chdir(char *str)
{
	int	fd;

	fd = 0;
	if (chdir((const char *)str) < 0)
	{
		fd = open(str, O_DIRECTORY);
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(str, 2);
		if (access(str, 0) < 0)
			ft_putendl_fd(": No such file or directory", 2);
		else if (fd < 0)
			ft_putendl_fd(": Permission denied", 2);
		if (fd > 0)
			close(fd);
			return (1);
	}
	return (0);
}

void	cd_back(t_obj *o)
{
	char	*way;
	char	*buf;
	char	*last;
	char	*prev;

	get_variable_env(o, &way, "PWD=", 4);
	buf = get_address();
	if (!buf)
		buf = way;
//	printf("||| %s\n", buf);
	last = ft_strrchr(buf, '/');
	prev = ft_substr(buf, 0, ft_strlen(buf) - ft_strlen(last));
	if (!prev)
		print_error("func back", "cd");
	do_chdir(prev);
	get_variable_env(o, &way, "PWD=", 4);
	mercury_repl_env(o, "OLDPWD=", way, 7);
	mercury_repl_env(o, "PWD=", prev, 4);
}

void	command_cd(t_obj *o)
{
	char	*way;

	mercury_repl_env(o, "_=", "cd", 2);
	if (!o->pipes->arg[1])
	{
		if (get_variable_env(o, &way, "HOME=", 5))
		{
			print_error(" : HOME not set", "cd");
			return ;
		}
		do_chdir(way);
		get_variable_env(o, &way, "PWD=", 4);
		mercury_repl_env(o, "OLDPWD=", way, 7);
		get_variable_env(o, &way, "HOME=", 5);
		mercury_repl_env(o, "PWD=", way, 4);
	}
	else if (o->pipes->arg[1] && !ft_strncmp(o->pipes->arg[1], "..", 3) && ft_strlen(o->pipes->arg[1]) == 2)
		cd_back(o);
	else if (!do_chdir(o->pipes->arg[1]))
	{
		get_variable_env(o, &way, "PWD=", 4);
		mercury_repl_env(o, "OLDPWD=", way, 7);
		mercury_repl_env(o, "PWD=", o->pipes->arg[1], 4);
	}
}