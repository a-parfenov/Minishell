
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <readline/readline.h>
# include "libft/libft.h"
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

typedef struct s_list
{
	char			**commands;
	struct s_list	*next;
}					t_list;

typedef struct s_obj
{
	char	**env;
	char	**heredoc;
	int		fd_in;
	int		fd_out;
	int		fd_re_out;
	int		is_heredoc;
	int		is_redirect;
	t_list	*pipes;
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
char	*get_next_line(int fd);

void	free_arr(char **arr);
int		ft_strcmp(char *s1, char *s2);
void	exe(t_obj *o);

#endif