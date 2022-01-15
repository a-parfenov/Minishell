/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:34:54 by aleslie           #+#    #+#             */
/*   Updated: 2022/01/15 14:45:31 by aleslie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include "../libft/libft.h"
# define SHELL_NAME "minishell% "
# define ERROR_NAME "minishell"
# define ONE_TOKEN "Error! Unclosed quote"
# define TWO_TOKEN "Error! Unclosed dquote"
# define SYNTAX_TOKEN "syntax error"
# define IN_TOKEN "syntax error near unexpected token `<'"
# define OUT_TOKEN "syntax error near unexpected token `>'"
# define PIPE_TOKEN "syntax error near unexpected token `|'"
# define NEW_TOKEN "syntax error near unexpected token `newline'"
# define BUFFER_SIZE 1024

typedef	struct s_link
{
	char			*str;
	struct s_link	*next;
}					t_link;

typedef struct s_pipes
{
	char			**arg;
	struct s_pipes	*next;
}					t_pipes;

typedef struct s_env
{
	char			*env_str;
	struct s_env	*next;
}					t_env;

typedef struct s_obj
{
	char	**env;
	char	**heredoc;
	int		fd_in;
	int		fd_out;
	int		fd_re_out;
	int		is_heredoc;
	int		is_redirect;
	t_env	*env_st;
	t_pipes	*pipes;
	t_link	*link;
}			t_obj;

t_obj	*init_o(char **env);

void	parse(char *input, t_obj *o);
char	*delete_spaces(char *input);
char	*parse_quote(char *input, int *index);
char	*parse_dquote(char *input, int *index);
char	*parse_dollar(char *input, int *index);
char	*find_dollar(char *mid);
char	*parse_in_redirect(char *input, int *index, t_obj *o);
char	*parse_heredoc(char *input, int *index, t_obj *o);
char	*parse_out_redirect(char *input, int *index, t_obj *o);
char	*parse_rewrite_redirect(char *input, int *index, t_obj *o);
char	*parse_pipe(char *input, int *index, t_obj *o);
char	*parse_spaces(char *input, int *index, t_obj *o);
char	*free_two_str(char *s1, char *s2);
char	*free_three_str(char *s1, char *s2, char *s3);
int		check_len(char *s);
int		check_token(char c);
int		check_token_two(char c);
void	pass_space_one(char *input, int *i);
void	pass_space_two(char *input, int *i);
char	*build_file(char *file);
void	put_str_to_link(char *str, t_obj *o);
void	put_link_to_pipe(t_obj *o);
char	*get_next_line(int fd);

t_link	*link_new_node(char *command);
void	link_add_back(t_link **link, t_link *new_node);
void	free_link(t_link **link);
int		link_size(t_link *link);
t_pipes	*pipes_new_node(char **arg);
void	pipes_add_back(t_pipes **pipes, t_pipes *new_node);
void	free_pipes(t_pipes **pipes);
int		pipes_size(t_pipes *pipes);

void	free_arr(char **arr);
int		ft_strcmp(char *s1, char *s2);
void	exe(t_obj *o);

void	print_error(char *error, char *str);

void	command_env(t_obj	*o);
void	command_pwd(t_obj *o);
void	command_echo(t_pipes	*pipes);
void	command_cd(t_obj *o);

#endif
