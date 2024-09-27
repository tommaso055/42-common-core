MLXPATH = $(CURDIR)/minilibx-linux
CFLAGS = -Wall -Wextra -Werror
LIBS = -L$(MLXPATH) -lmlx_Linux -lX11 -lXext
SRCS = so_long_main.c get_next_line_utils.c get_next_line.c so_long_flood_fill.c so_long_utils.c so_long_play.c ft_printf.c so_long_play_utils.c
OBJ = $(SRCS:.c=.o)
NAME = so_long

MLX_DIR = ./minilibx-linux
MLX_LIB = libmlx_Linux.a

all: $(NAME)

$(NAME): $(MLX_LIB) $(OBJ)
	gcc $(OBJ) $(LIBS) -o $@

%.o: %.c
	gcc $(CFLAGS) -c $<

$(MLX_LIB):
	$(MAKE) -C $(MLX_DIR)

clean:
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(MLX_DIR) fclean
	rm -f $(NAME)

re: fclean all
.PHONY: all clean fclean