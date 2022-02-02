/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:34:28 by aleslie           #+#    #+#             */
/*   Updated: 2022/02/02 22:37:58 by aleslie          ###   ########.fr       */
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
			temp->env_str = NULL;
			temp->env_str = ft_strjoin(str, way);
			break ;
		}
		temp = temp->next;
	}
}

static void	do_chdir(char *str)
{
	int	fd;

	fd = 0;
	fd = open(str, O_DIRECTORY);
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(str, 2);
	if (access(str, 0) < 0)
		ft_putendl_fd(": No such file or directory", 2);
	else if (fd < 0)
		ft_putendl_fd(": Permission denied", 2);
	if (fd > 0)
		close(fd);
}

static void	ways_cd(t_obj *o, char *way)
{
	char	d[2];
	char	*tmp;
	char	*tmp2;

	d[0] = '/';
	d[1] = '\0';
	if (chdir(o->pipes->arg[1]) > 0)
	{
		mercury_repl_env(o, "OLDPWD=", way, 7);
		mercury_repl_env(o, "PWD=", o->pipes->arg[1], 4);
		return ;
	}
	else if (o->pipes->arg[1][0] != d[0])
	{
		tmp2 = ft_strjoin(way, d);
		tmp = ft_strjoin(tmp2, o->pipes->arg[1]);
		free(tmp2);
		if (chdir(tmp) >= 0)
		{
			mercury_repl_env(o, "OLDPWD=", way, 7);
			mercury_repl_env(o, "PWD=", tmp, 4);
		}
		free(tmp);
	}
	else
		do_chdir(o->pipes->arg[1]);
	
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
		if (chdir(way))
			do_chdir(way);
		get_variable_env(o, &way, "PWD=", 4);
		mercury_repl_env(o, "OLDPWD=", way, 7);
		get_variable_env(o, &way, "HOME=", 5);
		mercury_repl_env(o, "PWD=", way, 4);
	}
	else if (o->pipes->arg[1] && !ft_strncmp(o->pipes->arg[1], "..", 2)
		&& ft_strlen(o->pipes->arg[1]) == 2)
		cd_back(o);
	else if (o->pipes->arg[1] && !ft_strncmp(o->pipes->arg[1], "-", 1)
		&& ft_strlen(o->pipes->arg[1]) == 1)
		ft_cd_home(o);
	else
	{
		get_variable_env(o, &way, "PWD=", 4);
		ways_cd(o, way);
	}
}
