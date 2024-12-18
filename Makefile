NAME = fdf
LIBFT = libft/
GNL = get_next_line/
MLX = minilibx/
SRC =	fdf.c/ \
			src/map/read_file.c \
			src/graphics/draw.c \

CC = cc

INCLUDE = includes

CC_FLAGS = -g -Wall -Wextra -Werror -I$(INCLUDE)

OBJS = $(SRC:.c=.o)


$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

clean:
	rm -f $(OBJS) 
fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

run: re
	clear
	$(CC) $(CC_FLAGS) main.c $(NAME)
	./a.out test_maps/42.fdf 1920 1080

r:
	make fclean -C $(LIBFT)
	make -C $(LIBFT)
	make clean -C $(LIBFT)
val:
	valgrind ./a.out test_maps/42.fdf

.PHONY: all clean fclean re run bonus
