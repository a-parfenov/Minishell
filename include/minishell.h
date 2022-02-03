/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aleslie <aleslie@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 19:34:54 by aleslie           #+#    #+#             */
/*   Updated: 2022/02/03 16:04:05 by aleslie          ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# define SHELL_NAME "minishell% "
# define ERROR_NAME "minishell"
# define ONE_TOKEN "Error! Unclosed quote"
# define TWO_TOKEN "Error! Unclosed dquote"
# define THREE_TOKEN "Error! Unclosed pipe"
# define SYNTAX_TOKEN "syntax error"
# define COMMAND_TOKEN "command not found"
# define IN_TOKEN "syntax error near unexpected token `<'"
# define OUT_TOKEN "syntax error near unexpected token `>'"
# define PIPE_TOKEN "syntax error near unexpected token `|'"
# define NEW_TOKEN "syntax error near unexpected token `newline'"
# define BUFFER_SIZE 1024
# define D "/"

int	g_exit;

typedef struct s_link
{
	char			*str;
	struct s_link	*next;
}					t_link;

typedef struct s_pipes
{
	int				index;
	char			**arg;
	char			*heredoc;
	struct s_pipes	*next;
	int				fd_in;
	int				fd_out;
	int				fd_re_out;
	int				is_heredoc;
	int				is_redirect;
	int				is_was_dollar;
}					t_pipes;

# define MIN 0
# define MAX 1

typedef struct s_env
{
	char			*env_str;
	struct s_env	*next;
	int				flag;
	struct s_env	*export_next;
}					t_env;

typedef struct s_obj
{
	char	**env;
	char	*heredoc;
	int		is_pipe;
	int		fd_in;
	int		fd_out;
	int		fd_re_out;
	int		is_heredoc;
	int		is_redirect;
	int		is_was_dollar;
	int		pipe_index;
	int		parse_flag;
	int		tmp_in;
	int		count_arg;
	char	*shlvl;
	int		pipe_fd_in;
	int		pipe_fd_out;
	t_env	*env_st;
	t_env	*env_export;
	t_pipes	*pipes;
	t_link	*link;
}			t_obj;

t_obj	*init_o(char **env);
void	re_init_o_fd(t_obj *o);

void	parse(char *input, t_obj *o);
char	*delete_spaces(char *input);
char	*parse_quote(char *input, int *index);
char	*parse_dquote(char *input, int *index, t_obj *o);
char	*parse_dollar(char *input, int *index, t_obj *o);
char	*find_dollar(char *mid, t_obj *o);
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
char	*build_file(char *file, t_obj *o);
char	*build_error_str(char *file);
void	put_str_to_link(char *str, t_obj *o);
void	put_link_to_pipe(t_obj *o);
char	*init_start(int *i, int *index, char *input);
char	*init_rewrite_start(int *i, int *index, char *input);
char	*get_next_line(int fd);

t_link	*link_new_node(char *command);
void	link_add_back(t_link **link, t_link *new_node);
void	free_link(t_link **link);
int		link_size(t_link *link);
t_pipes	*pipes_new_node(char **arg, t_obj *o);
void	pipes_add_back(t_pipes **pipes, t_pipes *new_node);
void	free_pipes(t_pipes **pipes);
int		pipes_size(t_pipes *pipes);

void	free_arr(char **arr);
int		ft_strcmp(char *s1, char *s2);

void	exe(t_obj *o);
void	free_env_struct(t_obj *o);

void	print_error(char *error, char *str);
void	close_fds(int fd1, int fd2, int fd3);
void	init_fds(int fd_in, int fd_out, int fd_re_out);
void	micro_print_err(char *command);
char	*find_command(char **arg);
char	*find_command_in_env(char *command);
void	exe_heredoc(t_pipes *pipes);
void	init_pipe_fds(int fd_in, int fd_out, t_obj *o);

void	exe(t_obj *o);
void	fake_exe(t_obj *o);
void	exe_command(t_obj *o);
int		check_pipe_redirects(t_pipes *pipe);

void	command_env(t_obj	*o);
void	command_pwd(t_obj *o);
void	command_echo(t_pipes	*pipes, t_obj *o);
void	command_cd(t_obj *o);
char	*get_address(void);
void	command_exit(char **code, t_obj *o);
void	command_export(t_obj *o);
void	sort_env(t_obj *o);
int		ft_strcmp_c(char s1, char s2);
int		ft_strchr_len(const char *s, int c);
void	command_unset(t_obj *o);
int		check_for_error_data(char *data, char c);
t_env	*find_env_data(t_env *env, char *data);
void	shell_level(t_obj *o);
void	add_new_data(t_obj *o, char *command);
char	**build_envp(t_env *env);
int		init_logic_fd(t_obj *o);
void	cd_back(t_obj *o);
int		get_variable_env(t_obj *o, char **adr, char *key_word, int n);
void	mercury_repl_env(t_obj *o, char *str, char *way, int symb);
int		ft_cd_prev(t_obj *o);
void	do_chdir(char *str);
void	pwd_check(t_env	*tmp, t_obj	*o);

t_env	*lst_new_env(char *arg);
int		lst_add_back(t_obj	*o, t_env *lst);

void	rl_replace_line(const char *buffer, int val);

#endif
