/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:27:14 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/31 18:20:35 by aleslie          ###   ########.fr       */
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
			return (1);
		i++;
	}
	return (-1);
}

void	shlvl(t_obj *o)
{
	int		tmp;
	char	*t;

	if (check_digit(o->shlvl))
	{
		tmp = ft_atoi(o->shlvl);
		if (tmp == 999)
			add_new_data(o, ft_strjoin("SHLVL=", ""));
		else if (tmp < 0)
			add_new_data(o, ft_strjoin("SHLVL=", "0"));
		else if (tmp < 1000)
		{
			t = ft_itoa(tmp + 1);
			add_new_data(o, ft_strjoin("SHLVL=", t));
			free(t);
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
	o->shlvl = NULL;
	while (o->env_st != NULL)
	{
		if (ft_strncmp(o->env_st->env_str, "SHLVL=", 6) == 0)
		{
			o->shlvl = ft_substr(o->env_st->env_str, 6, ft_strlen(o->env_st->env_str) - 6);
			// printf("%s %s\n", o->env_st->env_str, o->shlvl);
			break;
		}
		o->env_st = o->env_st->next;
	}
	shlvl(o);
}