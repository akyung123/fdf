NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDE = -I./include -I$(MLX_DIR) -I./libft -I./get_next_line -I./ft_printf

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

LIBFT_DIR = ./libft
PRINTF_DIR = ./ft_printf
GNL_DIR = ./get_next_line
MLX_DIR = ./minilibx-linux

LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a
GNL = $(GNL_DIR)/libgetnextline.a
MLX = $(MLX_DIR)/libmlx.a

LIBS = -L$(PRINTF_DIR) -L$(GNL_DIR) -L$(LIBFT_DIR) -L$(MLX_DIR)\
		-lftprintf -lgetnextline -lft -lmlx -lXext -lX11 -lm

.PHONY : all
all: $(LIBFT) $(PRINTF) $(GNL) $(MLX) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(PRINTF):
	make -C $(PRINTF_DIR)

$(GNL):
	make -C $(GNL_DIR)

$(MLX):
	make -C $(MLX_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBS) -o $(NAME)

.PHONY: clean
clean:
	rm -f $(OBJS)
	make -C $(LIBFT_DIR) clean
	make -C $(PRINTF_DIR) clean
	make -C $(GNL_DIR) clean
	make -C $(MLX_DIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C $(PRINTF_DIR) fclean
	make -C $(GNL_DIR) fclean
	make -C $(MLX_DIR) fclean

.PHONY: re
re: fclean all