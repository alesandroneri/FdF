NAME = fdf

LIBFT_PATH=	libft/
MINILIB_PATH= minilibx-linux/

LIBFT_A=	$(LIBFT_PATH)libft.a
MINILIB_A= 	$(MINILIB_PATH)libmlx_linux.a

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
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_PATH) -lft -L $(MINILIB_PATH) -lmlx -lX11 -lXext -lft -lm -lz -o $(NAME)

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

run: $(NAME)
	@clear
	@./$(NAME) ./mwx.fdf

r:
	make fclean -C $(LIBFT)
	make -C $(LIBFT)
	make clean -C $(LIBFT)
val:
	valgrind ./a.out test_maps/42.fdf

.PHONY: all clean fclean re run bonus
