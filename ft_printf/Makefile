CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
CREATELIB = ar -rcs
ADDLIB = ranlib
SRCS = ft_printf.c
OBJECTS = $(SRCS:.c=.o)
RM = rm -f

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CREATELIB) $(NAME) $(OBJECTS)
	$(ADDLIB) $(NAME)

clean: 
	$(RM) $(OBJECTS)
	$(RM) $(BONUS_OBJ)

fclean: clean 
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re bonus