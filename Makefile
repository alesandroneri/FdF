NAME = fdf
LIBFT = libft/
MLX = minilibx-linux/
SRC =	fdf.c \
		src/map/read_file.c \
		src/graphics/draw.c \
		src/free/free_utils.c \
		src/hook/handle_hooks.c \
		src/hook/key_hooks.c

CC = cc

INCLUDE = includes

CC_FLAGS = -g -Wall -Wextra -Werror -I$(INCLUDE)

OBJS = $(SRC:.c=.o)


$(NAME): $(OBJS)
	$(CC) $(CC_FLAGS) $(OBJS) -L libft/libft.a minilibx-linux/libmlx.a -lmlx -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

clean:
	rm -f $(OBJS) 
fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)
	make fclean -C $(LIBFT)
	make fclean -C $(MLX)

run: re
	clear
	$(CC) $(CC_FLAGS) main.c $(NAME)
	./a.out test_maps/42.fdf

r:
	make fclean -C $(LIBFT)
	make -C $(LIBFT)
	make clean -C $(LIBFT)
val:
	valgrind ./a.out test_maps/42.fdf

.PHONY: all clean fclean re run bonus
