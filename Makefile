NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -lreadline

all: $(NAME)

$(NAME): src/*.c
	$(CC) $(FLAGS) src/*.c libft/libft.a -o $(NAME)

clean:
	rm -rf minishell

re: clean all
