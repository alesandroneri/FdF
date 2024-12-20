NAME = libft.a

SRCS =	ft_strchr.c \
	ft_strdup.c \
	ft_atoi.c \
	ft_strjoin.c \
	ft_strlcpy.c \
	ft_split.c \
	ft_strlen.c \
	ft_atoi_base.c \
	ft_isdigit.c \
	ft_putendl_fd.c \
	ft_atoi_hexa.c \
	ft_itoa.c \
	ft_printf/ft_printf.c \
	ft_printf/ft_putstr_count.c \
	ft_printf/ft_putnbr_count.c \
	ft_printf/ft_putnbr_base_count.c \
	ft_printf/ft_putchar_count.c \
	ft_printf/ft_put_ptr.c \
	get_next_line/get_next_line.c 

CC = cc

CC_FLAGS = -g -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

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
	./a.out

.PHONY: all clean fclean re run
