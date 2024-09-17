CFLAGS = #-Wall -Wextra -Werror
LIBS = -L/nfs/homes/tdonato/42/so_long/minilibx-linux -lmlx_Linux -lX11 -lXext
SRCS = so_long_main.c get_next_line_utils.c get_next_line.c so_long_flood_fill.c  so_long_utils.c so_long_play.c
OBJ = $(SRCS:.c=.o)

all: myprogram clean

myprogram: $(SRCS)
	gcc $(CFLAGS) -c $(SRCS)
	gcc $(OBJ) $(LIBS) -o so_long

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(OBJ) so_long

re: fclean all
.PHONY: all clean fclean