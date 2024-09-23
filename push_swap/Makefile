CFLAGS = #-Wall -Wextra -Werror
SRCS = push_swap.c push_swap_algorithm.c push_swap_utils.c push.c reverse_rotate.c rotate.c swap.c
OBJ = $(SRCS:.c=.o)

all: myprogram clean

myprogram: $(SRCS)
	gcc $(CFLAGS) -c $(SRCS)
	gcc $(OBJ) -o test

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) test

re: fclean all
.PHONY: all clean fclean