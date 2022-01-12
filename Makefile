NAME	= minishell

SRCS	=	main.c\
			init.c exe.c\
			parsing/parse.c\
			parsing/delete_spaces.c\
			parsing/parse_quote.c\
			parsing/parse_dquote.c\
			parsing/parse_dollar.c\
			parsing/parse_in_redirect.c\
			parsing/parse_heredoc.c\
			parsing/parse_out_redirect.c\
			parsing/parse_rewrite_redirect.c\
			parsing/parse_pipe.c\
			parsing/parse_spases.c\
			parsing/parse_utils.c\
			parsing/parse_utils_two.c\
			parsing/get_next_line.c\
			utils_one.c\

OBJS	= $(SRCS:.c=.o)

HEADER	= minishell.h

CFLAGS	= -Wall -Wextra -Werror -I $(HEADER)

CC		= gcc

LIB		= libft/libft.a

.PHONY: all clean fclean re

all: $(LIB) $(NAME)

$(NAME): $(OBJS) $(HEADER)
	$(CC) $(CFLAGS) -lreadline -L libft -lft $(OBJS) -o $@

$(LIB):
	make -C libft

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all