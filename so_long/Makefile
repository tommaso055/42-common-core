CFLAGS = #-Wall -Wextra -Werror
LIBS = -L/nfs/homes/tdonato/42/so_long/minilibx-linux -lmlx_Linux -lX11 -lXext

all: myprogram clean

myprogram: main.o
	gcc main.o $(LIBS) -o so_long

main.o: main.c
	gcc $(CFLAGS) -c main.c

clean:
	rm -f *.o

fclean:
	rm -f *.o so_long

re: fclean all
.PHONY: all clean fclean