CFLAGS = #-Wall -Wextra -Werror
LIBS = -L/nfs/homes/tdonato/42/so_long/minilibx-linux -lmlx_Linux -lX11 -lXext

all: myprogram clean

myprogram: so_long_main.o
	gcc so_long_main.o $(LIBS) -o so_long

so_long_main.o: so_long_main.c
	gcc $(CFLAGS) -c so_long_main.c

clean:
	rm -f *.o

fclean:
	rm -f *.o so_long

re: fclean all
.PHONY: all clean fclean