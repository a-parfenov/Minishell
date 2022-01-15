/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 13:34:28 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/15 11:23:57 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	get_variable_env(t_obj *o, char **adr, char *key_word, int n)
{
	int		i;

	i = -1;
	while (o->env[++i])
	{
		if (ft_strncmp(o->env[i], key_word, n) == 0)
		{
			*adr = o->env[i] + n;
			return (0);
		}
	}
	return (1);
}

// void	do_oldpwd(t_obj *o)
// {
// 	t_obj	*my_str;

// 	my_str = find_on_head(env, "OLDPWD");
// 	free(my_str->content);
// 	my_str->content = find_on_head(env, "PWD")->content;
// }

void	command_cd(t_obj *o)
{
	char	*home;
	char	*full_path;
	int		check_dir;

	home = NULL;
	if (o->pipes->arg[1] == NULL)
	{
		if (get_variable_env(o, &home, "HOME=", 5))
		{
			print_error(" : HOME not set", "cd");
			return ;
		}
	}
	printf("|| %s\n", home);
	home = getenv("HOME");
	printf("|| %s\n", home);
	check_dir = chdir(home);
	printf("|| %s\n", o->pipes->arg[1]);
	printf("|| %d\n", check_dir);
	full_path = NULL; //malloc(1024);
	getcwd(full_path, 1024);
	if (check_dir == -1)
		print_error(" : No such file or directory", "cd");
	


	
	// if (!o->pipes->arg || o->pipes->arg[0])
		
	// if (get_variable_env(o, &home, "HOME=", 5))
	// {
	// 	ft_putendl_fd("Error cd: HOME not set", 1);
	// 	return ;
	// }
	// printf("|| %s\n", home);
	// printf("|| %s\n", home);
	// (o->pipes->arg[1] + 1 == '\0' && ft_strncmp(o->pipes->arg[1], ".", 1))
	// if (!o->pipes->arg[1])
	// {
	// 	chdir(home);
	// 	printf("|---|\n");
		
	// }	
	// printf("|| %s\n", o->pipes->arg[1] + 1);
	return ;
}