NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror 
LDFLAGS = -lreadline
LIBFT = libft/libft.a
SRC = src/main.c \
	  src/builtcmd.c \
	  src/input_parser.c\
	  src/utils_directory.c\

all: $(NAME)

$(NAME): src/*.c $(LIBFT)
	$(CC) $(FLAGS) $(SRC) $(LIBFT) $(LDFLAGS)  -o $(NAME)

$(LIBFT):
	make -C libft/

clean:
	rm -rf minishell

re: clean all
