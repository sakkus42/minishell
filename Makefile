NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -I./lib/readline/include
LDFLAGS = -L./lib/readline/lib -lreadline
SRC = src/main.c \
	  src/builtcmd.c \
	  src/input_parser.c\
	  src/utils_directory.c\

all: $(NAME)

$(NAME): src/*.c
	$(CC) $(FLAGS) $(LDFLAGS) $(SRC) libft/libft.a -o $(NAME)

clean:
	rm -rf minishell

re: clean all
