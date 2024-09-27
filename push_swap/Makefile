NAME = push_swap
CFLAGS = -Wall -Wextra -Werror
SRCS = push_swap.c push_swap_algorithm.c push_swap_utils.c push.c reverse_rotate.c rotate.c swap.c push_swap_more_utils.c push_swap_extra.c ft_split.c check_input.c
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