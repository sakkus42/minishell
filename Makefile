NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror -I./lib/readline/include
LDFLAGS = -L./lib/readline/lib -lreadline

all: $(NAME)

$(NAME): src/*.c
	$(CC) $(FLAGS) $(LDFLAGS) src/*.c libft/libft.a -o $(NAME)

clean:
	rm -rf minishell

re: clean all
