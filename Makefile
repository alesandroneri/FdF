NAME = fdf

LIBFT_PATH=	libft/
MINILIB_PATH= minilibx-linux/

LIBFT_A=	$(LIBFT_PATH)libft.a
MINILIB_A= 	$(MINILIB_PATH)libmlx_linux.a

SRC =	fdf.c \
		src/map/read_file.c \
		src/map/read_file_utils.c \
		src/graphics/draw.c \
		src/graphics/draw_utils.c \
		src/graphics/graphics_features.c \
		src/graphics/panel_utils.c \
		src/free/free_utils.c \
		src/hook/handle_hooks.c \
		src/hook/key_hooks.c

CC = cc

CC_FLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRC:.c=.o)

all: $(MINILIB_A) $(LIBFT_A) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L $(LIBFT_PATH) -lft -L $(MINILIB_PATH) -lmlx -lX11 -lXext -lft -lm -lz -o $(NAME)

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $(<:.c=.o)

$(MINILIB_A):
	@make -C $(MINILIB_PATH)

$(LIBFT_A):
	@make -C $(LIBFT_PATH)

clean:
	@rm -f $(OBJS) 
	@make clean -C $(MINILIB_PATH)
	@make clean -C $(LIBFT_PATH)

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@make clean -C $(MINILIB_PATH)
	@rm -rf $(NAME)

re: fclean $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@make clean -C $(MINILIB_PATH)

run: $(NAME)
	@clear
	@./$(NAME) ./test_maps/julia.fdf

r:
	@make fclean -C $(LIBFT_PATH)
	@make -C $(LIBFT_PATH)
	@make clean -C $(LIBFT_PATH)

val:
	@valgrind ./fdf test_maps/42.fdf

comment:
	@find . -type f -iname "*.c" -exec grep "//" {} +

.PHONY: all clean fclean re run 
