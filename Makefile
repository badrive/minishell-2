
NAME = minishell

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 #-fsanitize=address

SRCS = main.c \
	parsing/parsing.c parsing/split.c parsing/utils1.c parsing/utils2.c\
	parsing/lst/lst_cmd.c parsing/lst/lst_heredoc.c parsing/utils3.c parsing/anti_leaks.c \
	parsing/lst/lst_lexer.c parsing/lst/lst_redir.c parsing/ft_split_s.c \
	execution/builtin_cd.c execution/builtin_env.c \
	execution/builtin_unset.c execution/execution.c \
	execution/builtin_echo.c execution/builtin_pwd.c \
	execution/builtin_export.c execution/builtin_exit.c \
	execution/utils.c execution/utils1.c execution/red_utils.c \


OBJS = $(SRCS:.c=.o)

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) -lreadline

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
