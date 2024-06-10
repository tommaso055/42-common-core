CC = gcc
CFLAGS = -Wall -Wextra -Werror
NAME = libft.a
CREATELIB = ar -rcs
ADDLIB = ranlib
SRCS = ft_putchar_fd.c ft_atoi.c ft_putendl_fd.c \
ft_bzero.c ft_putnbr_fd.c ft_calloc.c ft_putstr_fd.c \
ft_isdigit.c ft_split.c ft_isalnum.c \
ft_isalpha.c ft_strchr.c ft_isascii.c ft_strdup.c \
ft_isprint.c ft_striteri.c ft_itoa.c ft_strjoin.c ft_strlcat.c \
ft_strlcpy.c ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c \
ft_strrchr.c ft_strtrim.c ft_substr.c ft_memchr.c ft_tolower.c \
ft_memcmp.c ft_toupper.c ft_memcpy.c ft_memmove.c ft_memset.c
BONUS = ft_lstadd_back.c \
ft_lstadd_front.c ft_lstclear.c \
ft_lstdelone.c ft_lstiter.c \
ft_lstlast.c ft_lstmap.c \
ft_lstnew.c ft_lstsize.c
OBJECTS = $(SRCS:.c=.o)
BONUS_OBJ = $(BONUS:.c=.o)
RM = rm -f
INCL = includes

all: $(NAME)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCL)

$(NAME): $(OBJECTS)
	$(CREATELIB) $(NAME) $(OBJECTS)
	$(ADDLIB) $(NAME)

bonus: $(BONUS_OBJ)
	$(CREATELIB) $(NAME) $(BONUS_OBJ)
	$(ADDLIB) $(NAME)
	
clean: 
	$(RM) $(OBJECTS)
	$(RM) $(BONUS_OBJ)

fclean: clean 
	$(RM) $(NAME)

re: fclean all
.PHONY: all clean fclean re bonus