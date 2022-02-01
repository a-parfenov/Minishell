/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 23:30:21 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/26 16:24:33 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_envsize(t_env *lst)
{
	int	amount;

	amount = 0;
	while (lst)
	{
		lst = lst->next;
		amount++;
	}
	return (amount);
}

char	**build_envp(t_env *env)
{
	char	**envp;
	int		count;

	count = 0;
	envp = malloc(sizeof(char *) * (ft_envsize(env) + 1));
	if (!envp)
	{
		print_error("sort_env", "malloc");
		exit(1);
	}
	while (env)
	{
		envp[count++] = env->env_str;
		env = env->next;
	}
	envp[count] = NULL;
	return (envp);
}

int	ft_strchr_len(const char *s, int c)
{
	char	d;
	int		i;

	d = c - '0';
	i = 0;
	while (*s)
	{
		if (*s == c)
			return (i);
		s++;
		i++;
	}
	return (-1);
}

void	print_export_data(char **data)
{
	int		a;
	int		len;
	char	*key;

	a = 0;
	while (data[a])
	{
		ft_putstr_fd("declare -x ", 1);
		len = ft_strchr_len(data[a], '=');
		if (len == -1)
			ft_putendl_fd(data[a], 1);
		else
		{
			key = ft_substr(data[a], 0, len + 1);
			ft_putstr_fd(key, 1);
			free(key);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(data[a] + len + 1, 1);
			ft_putendl_fd("\"", 1);
		}
		a++;
	}
}

void	sort_env(t_obj *o)
{
	char	**data;
	char	*temp;
	int		a;
	int		b;

	data = build_envp(o->env_st);
	a = 0;
	while (data[a])
	{
		b = 0;
		while (data[b+1])
		{
			if (ft_strncmp(data[b], data[b + 1], ft_strlen(data[b])) > 0)
			{
				temp = data[b];
				data[b] = data[b + 1];
				data[b + 1] = temp;
			}
			b++;
		}
		a++;
	}
	print_export_data(data);
	free(data);
}
