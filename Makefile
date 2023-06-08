NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -g
LDFLAGS = -lreadline
LIBFT = libft/libft.a
SRC = src/main.c \
	  src/signal.c \
	  src/lexer/lexer.c \
	  src/lexer/skip.c \
	  src/lexer/control.c \
	  src/lexer/utils.c \
	  src/lexer/add_token.c \
	  src/lexer/parser.c \
	  src/lexer/add_dolar.c \
	  src/utils/utils_directory.c \
	  src/utils/free_all.c \
	  src/utils/linked_list_utils.c \
	  src/utils/is_builtin.c\
	  src/utils/ft_strcmp.c\
	  src/utils/init.c\
	  src/exec/exec_cmnd.c \
	  src/builtin/export.c	\
	  src/builtin/unset.c	\
	  src/builtin/builtins.c \
	  src/builtin/cd.c \
	  src/builtin/environment_utils.c \
	  src/builtin/environment.c \
	  src/builtin/free_double.c \
	  src/builtin/keyvals.c  \
	  src/builtin/exit_utils.c  \

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(FLAGS) $(SRC) $(LIBFT) $(LDFLAGS)  -o $(NAME)

$(LIBFT):
	make -C libft/

clean:
	rm -rf minishell

re: clean all

# parser dosyasında herhangi bir değişkliği görmüyor