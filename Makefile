NAME	=	minishell

SRCS	=	src/main.c\
			src/init.c\
			src/exe.c\
			src/utils_one.c\
			src/link.c\
			src/pipes.c\
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
			logic/env.c\
			logic/pwd.c

OBJS	=	$(SRCS:.c=.o)

INCLUDE	=	include/

HEADER	=	minishell.h

CFLAGS	=	-Wall -Wextra -Werror

CC		=	gcc

LIB		=	libft/libft.a

RED			=	"\033[1;31m"
BLUE		=	"\033[1;34m"
YELLOW		=	"\033[1;33m"
WHITE		=	"\033[1;37m"
GREEN		=	"\033[1;32m"
PURPLE		=	"\033[1;35m"
GRAY		=	"\033[1;30m"
END			=	"\033[0m"

.PHONY: all clean fclean re 

all: $(LIB) $(NAME)

$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) -lreadline -L libft -lft $(OBJS) -o $@
			@echo ${GREEN} "\n< Minishell binary -> done >\n" ${END}

$(LIB):
			@make -C libft

%.o:		%.c $(INCLUDE)$(HEADER)
			@$(CC) $(CFLAGS) -c $< -o $@ -I $(INCLUDE)

clean:
			@make $@ -C libft
			@$(RM) $(OBJS) OBJS
			@echo ${YELLOW} "\n< .o files -> removed >\n" ${END}

fclean: clean
			@make $@ -C libft
			@$(RM) $(NAME) NAME
			@echo ${YELLOW} "\n< Binaries -> removed >\n" ${END}

re: fclean all
			@echo ${PURPLE} "\n< Remake done >\n" ${END}