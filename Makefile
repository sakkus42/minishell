NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -I./lib/readline/include
LDFLAGS = -L./lib/readline/lib -lreadline
LIBFT = libft/libft.a
SRC = src/main.c \
	  src/builtcmd.c \
	  src/input_parser.c\
	  src/utils_directory.c\
	  src/signal.c\

all: $(NAME)

$(NAME): src/*.c $(LIBFT)
	$(CC) $(FLAGS) $(SRC) $(LIBFT) $(LDFLAGS)  -o $(NAME)

$(LIBFT):
	make -C libft/

clean:
	rm -rf minishell

re: clean all
