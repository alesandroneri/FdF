NAME = fdf
LIBFT = libft/
GNL = get_next_line/
MLX = minilibx/
SRC =	fdf.c \
		srcs/ \
		

CC = cc

INCLUDE = includes

CC_FLAGS = -g -Wall -Wextra -Werror -I$(INCLUDE)

OBJS = $(SRC:.c=.o)

BONUS_OBJS = $(BONUS_SRC:.c=.o)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

.c.o:
	$(CC) $(CC_FLAGS) -c $< -o $(<:.c=.o)

all: $(NAME)

bonus: $(BONUS_OBJS) $(NAME)
	ar rc $(NAME) $(BONUS_OBJS)

clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)

run: re
	clear
	$(CC) $(CC_FLAGS) main.c $(NAME)
	./a.out

r:
	make fclean -C $(LIBFT)
	make -C $(LIBFT)
	make clean -C $(LIBFT)
	$(CC) -g main.c read_file.c $(LIBFT)libft.a
val:
	valgrind ./a.out test_maps/42.fdf

.PHONY: all clean fclean re run bonus
