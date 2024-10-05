NAME = pipex
CFLAGS = -Wall -Wextra -Werror
SRCS = ft_split.c pipex_main.c pipex_utils.c
OBJ = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	gcc $(OBJ) -o $(NAME)

%.o: %.c
	gcc $(CFLAGS) -c $<

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) $(NAME)

re: fclean all
.PHONY: all clean fclean