CFLAGS = -Wall -Wextra -Werror
SRCS = push_swap.c push_swap_algorithm.c push_swap_utils.c push.c reverse_rotate.c rotate.c swap.c push_swap_more_utils.c push_swap_extra.c
OBJ = $(SRCS:.c=.o)

all: myprogram clean

myprogram: $(SRCS)
	gcc $(CFLAGS) -c $(SRCS)
	gcc $(OBJ) -o push_swap

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) push_swap

re: fclean all
.PHONY: all clean fclean