NAME = minishell
CC = gcc
FLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline
LIBFT = libft/libft.a
SRC = src/main.c \
	  src/utils_directory.c \
	  src/signal.c \
	  src/lexer/lexer.c \
	  src/lexer/skip.c \
	  src/lexer/control.c \
	  src/lexer/utils.c \

all: $(NAME)

$(NAME): $(SRC) $(LIBFT)
	$(CC) $(FLAGS) $(SRC) $(LIBFT) $(LDFLAGS)  -o $(NAME)

$(LIBFT):
	make -C libft/

clean:
	rm -rf minishell

re: clean all

# parser dosyasında herhangi bir değişkliği görmüyor