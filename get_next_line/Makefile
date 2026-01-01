NAME = libgetnextline.a
SRCS = get_next_line.c
OBJS = $(SRCS:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f
HEADER = get_next_line.h

.PHONY: all
all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $@ $^

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: bonus
bonus : $(OBJS)
	@ar rcs $(NAME) $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
