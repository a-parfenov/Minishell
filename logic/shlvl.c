/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:27:14 by aleslie           #+#    #+#             */
/*   Updated: 2022/02/02 22:17:09 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_digit(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	shlvl(t_obj *o, char	**shlvl)
{
	int		tmp;
	char	*shlvl_n;

	if (check_digit(o->shlvl))
	{
		tmp = ft_atoi(o->shlvl);
		if (tmp == 999)
			add_new_data(o, ft_strjoin("SHLVL=", ""));
		else if (tmp < 0)
			add_new_data(o, ft_strjoin("SHLVL=", "0"));
		else if (tmp < 1000)
		{
			shlvl_n = ft_itoa(tmp + 1);
			*shlvl = ft_strjoin("SHLVL=", shlvl_n);
			add_new_data(o, *shlvl);
			free(shlvl_n);
		}
		else
		{
			print_error("", "shell level (1000) too high, resetting to 1");
			add_new_data(o, ft_strjoin("SHLVL=", "1"));
		}
	}
	else
		add_new_data(o, ft_strjoin("SHLVL=", "1"));
}

void	shell_level(t_obj *o)
{
	t_env	*tmp;
	char	*t1;

	o->shlvl = NULL;
	tmp = o->env_st;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->env_str, "SHLVL=", 6) == 0)
		{
			o->shlvl = ft_substr(tmp->env_str, 6, ft_strlen(tmp->env_str) - 6);
			break;
		}
		tmp = tmp->next;
	}
	t1 = NULL;
	shlvl(o, &t1);
	free(o->shlvl);
	free(t1);
}