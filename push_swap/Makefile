NAME = push_swap
CFLAGS = -Wall -Wextra -Werror
SRCS = push_swap.c push_swap_algorithm.c push_swap_utils.c push.c reverse_rotate.c rotate.c swap.c push_swap_more_utils.c push_swap_extra.c ft_split.c
OBJ = $(SRCS:.c=.o)

all: $(NAME) clean

$(NAME): $(SRCS)
	gcc $(CFLAGS) -c $(SRCS)
	gcc $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) $(NAME)

re: fclean all
.PHONY: all clean fclean