NAME = libftprintf.a
SRCS = 	ft_handle.c ft_printf.c ft_put_fuction.c printf_hex.c \
		ft_printf_format.c ft_vftprintf.c printf_unit.c \
		printf_chars.c printf_int.c pritnf_pointer.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
HEADER = ft_printf_bonus.h

.PHONY: all
all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS)
	@ar rcs $@ $^

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
