# Compiler and compiler flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Name of the library
NAME = libft.a

# Source and object files
SRCS = ft_isdigit.c \
       ft_isalnum.c \
       ft_isalpha.c \
       ft_isascii.c \
       ft_isprint.c \
       ft_isspace.c \
       ft_strlen.c \
       ft_memset.c \
       ft_bzero.c \
       ft_memcpy.c \
       ft_memmove.c \
       ft_strlcpy.c \
       ft_strcpy.c \
       ft_strncpy.c \
       ft_strlcat.c \
       ft_toupper.c \
       ft_tolower.c \
       ft_strchr.c \
       ft_strrchr.c \
       ft_strcmp.c \
       ft_strncmp.c \
       ft_memchr.c \
       ft_memcmp.c \
       ft_strnstr.c \
       ft_atoi.c \
       ft_atol.c \
       ft_calloc.c \
       ft_strdup.c \
       ft_strndup.c \
       ft_substr.c \
       ft_strjoin.c \
       ft_strtrim.c \
       ft_split.c \
       ft_itoa.c \
       ft_strmapi.c \
       ft_striteri.c \
       ft_putchar_fd.c \
       ft_putstr_fd.c \
       ft_putstr.c \
       ft_putendl_fd.c \
       ft_putnbr_fd.c \
       ft_putnbr_fd_ulong.c \
       ft_putnbr_fd_longlong.c \
       ft_lutoa.c \
       ft_llutoa.c \
       ft_ullonglen.c \
       ft_ulonglen.c \
       ft_abs.c \
       ft_intlen.c \
       ft_putnbr_base.c \
       ft_putuintnbr_base.c \
       ft_putulonglongnbr_base.c \
       ft_printf.c \
       ft_printf_processors_one.c \
       ft_printf_processors_two.c \
       ft_printf_utils.c \
       get_next_line.c \
       get_next_line_utils.c \
       ft_lstadd.c \
       ft_lstiter.c \
       ft_lstnew.c \
       ft_lstdelone.c \
       ft_lstdel.c \
       ft_lstmap.c \
       ft_min.c \
       ft_max.c \
       old_gnl.c \
       ft_memdel.c \
       ft_strnew.c \
       ft_strsub.c \
       ft_strdel.c

OBJS = $(SRCS:.c=.o)

# Rule to make the objects
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Rule to make the library
$(NAME): $(OBJS)
	ar rcs $@ $^

# Phony targets
.PHONY: all clean fclean re

# Standard make targets
all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
