#include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <fcntl.h>


# define MALLOC_ERROR 1
# define READ_FILE_ERROR 1

typedef struct s_point
{
	int	value;
	char *hex;
} t_point ;

typedef struct s_wfm
{
	int	width;
	int	height;
	t_point	**z_matrix;
	int zoom;
	int color;
	int shift_x;
	int shift_y;

	void	*mlx_ptr;
	void	*win_ptr;
}	t_wfm;

char	*ft_strdup(const char *s)
{
	char	*copy;
	int		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	copy = (char *)malloc(sizeof(char) * (i + 1));
	if (copy == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	src_size;

	src_size = ft_strlen(src);
	if (size == 0)
		return (src_size);
	i = 0;
	while ((i < size - 1) && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_size);
}

static int	count_words(char const *str, char sep)
{
	int	count;
	int	word;
	int	i;

	count = 0;
	word = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != sep && word == 0)
		{
			count++;
			word = 1;
		}
		else if (str[i] == sep)
			word = 0;
		i++;
	}
	return (count);
}

static int	safe_malloc(char **strs, int pos, int buffer)
{
	int	i;

	i = 0;
	strs[pos] = (char *)malloc(sizeof(char) * buffer);
	if (strs[pos] == NULL)
	{
		while (i < pos)
			free(strs[i++]);
		free(strs);
		return (1);
	}
	return (0);
}

static char	save_words(char **strs, char const *str, char sep)
{
	int	length;
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		length = 0;
		while (str[i] == sep && str[i])
			i++;
		while (str[i] != sep && str[i])
		{
			length++;
			i++;
		}
		if (length)
		{
			if (safe_malloc(strs, j, length + 1))
				return (1);
			ft_strlcpy(strs[j++], &str[i - length], length + 1);
		}
	}
	return (0);
}

int		is_base(char c, int base)
{
	char low_base[17] = "0123456789abcdef";
	char upper_base[17] = "0123456789ABCDEF";

	while (base--)
		if (low_base[base] == c || upper_base[base] == c)
			return (1);
	return (0);
}

int		valid_value(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	else if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	else if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int		ft_atoi_base(const char *str, int str_base)
{
	int result;
	int sign;
    int i;

    i = 0;
	result = 0;
    sign = 1;
	if (str == NULL || str_base < 2 || str_base > 16)
		return (0);
	while (str[i] <= 32 || str[i] == 127)
		i++;
    if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
            i = i + 2;
	while (str[i] == '-' || str[i] == '+')
    {
            if (str[i] == '-')
                sign *= -1;
            if (str[i + 1] == '-' || str[i + 1] == '+')
                return (0); 
        i++;
    }
	while (is_base(str[i], str_base))
		result = (result * str_base) + valid_value(str[i++]);
	return (result * sign);
}

int	ft_count_words(char const *str, char sep)
{
	int	count;
	int	word;
	int	i;

	count = 0;
	word = 0;
	i = 0;
	while (str != NULL && str[i] != '\0')
	{
		if (str[i] != sep && word == 0)
		{
			count++;
			word = 1;
		}
		else if (str[i] == sep)
			word = 0;
		i++;
	}
	return (count);
}

int	get_height(char *file_name)
{
	char	*line;
	int	height;
	int	fd;
	
	height = 0;
	fd = open(file_name, O_RDONLY, 0);
	if (fd < 0)
		return (-1);
	while ((line = get_next_line(fd)) != NULL)
	{
		height++;
		free(line);
		line = NULL;
	}
	close(fd);
	return (height);
}

int	get_width(char *file_name)
{
	char	*line;
	int	width;
	int	fd;

	fd = open(file_name, O_RDONLY, 0);
	line = get_next_line(fd);
	if (line != NULL)
	{
		width = ft_count_words(line, ' ');
		free(line);
		line = NULL;
	}
	while ((line = get_next_line(fd)) != NULL)
		free(line);
	close(fd);
	return (width);
}

int check_color(char *num, t_point *z_line)
{
	char **value_and_color;

    value_and_color = ft_split(num, ',');
    if (!value_and_color)
        return (0);
    if (value_and_color[1] == NULL)
	{
        z_line->value = ft_atoi(value_and_color[0]);
        z_line->hex = ft_strdup("0xFFFFFF");
    }
	else
	{
        z_line->value = ft_atoi(value_and_color[0]);
        z_line->hex = ft_strdup(value_and_color[1]);
    }
    free(value_and_color[0]);
    if (value_and_color[1])
        free(value_and_color[1]);
    free(value_and_color);
    return (1);
}



void	fill_matrix(t_point *z_line, char *line)
{
	char	**nums;
	int		i;
	char	**value_and_color;
	i = 0;
	nums = ft_split(line, ' ');
	if (!nums)
	{
		free(line);
		return ;
	}
	while(nums[i] != NULL)
	{
		if (!check_color(nums[i], &z_line[i]))
		{
			free(nums[i]);
			continue ;
		}
		free(nums[i]);
		i++;
	}
	free(nums);
}

void	read_file(char *file_name, t_wfm *data)
{
	char	*line;
	int	fd;
	int	i;

	data->height = get_height(file_name);
	data->width = get_width(file_name);
	data->z_matrix = (t_point **)malloc(sizeof(t_point *) * (data->height + 1));
	if (!data->z_matrix)
		return ;
	i = 0;
	while (i < data->height)
	{
		data->z_matrix[i] = (t_point *)malloc(sizeof(t_point) * (data->width));
		if (!data->z_matrix[i])
    	{
			while (i >= 0)
				free(data->z_matrix[--i]);
			free(data->z_matrix);
            	return ;
    	}
		i++;
	}
	fd = open(file_name, O_RDONLY, 0);
	i = 0;
	while((line = get_next_line(fd)) != NULL)
	{
		fill_matrix(data->z_matrix[i], line);
		free(line);
		i++;
	}
	close(fd);
}

int maximum(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}
float mod(float i)
{
    if (i < 0)
        return (-i);
    return (i);
}
void isometric (float *x, float *y, int z)
{
    *x = (*x - *y) * cos(0.8);
    *y = (*x + *y) * sin(0.8) - z;
}

void bresenham(float x, float y, float x1, float y1, t_wfm *data)
{
    float x_step;
    float y_step;
    int max;
    int z;
    int z1;
    int starting_color;

    z = data->z_matrix[(int)y][(int)x].value;
    z1 = data->z_matrix[(int)y1][(int)x1].value;

    //zoom
    x *= data->zoom;
    y *= data->zoom;
    x1 *= data->zoom;
    y1 *= data->zoom;
    //color
    starting_color = ft_atoi_base(data->z_matrix[(int)y][(int)x].hex, 16);
    //3D
    isometric(&x, &y, z);
    isometric(&x1, &y1, z1);
    //shift
    x += data->shift_x;
    y += data->shift_y;
    x1 += data->shift_x;
    y1 += data->shift_y;

    x_step = x1 - x;
    y_step = y1 - y;

    max = maximum(mod(x_step), mod(y_step));
    x_step /= max;
    y_step /= max;
    while ((int)(x - x1) || (int)(y - y1))
    {
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, starting_color);
        x += x_step;
        y += y_step;
    }
}

 void draw(t_wfm *data)
 {
     int x;
     int y;

     y = 0;
     while(y < data->height)
     {
         x = 0;
         while(x < data->width)
         {
            if (x < data->width - 1)
                bresenham(x, y, x + 1, y, data);
            if (y < data->height - 1)
                bresenham(x, y, x, y + 1, data);
             x++;
         }
         y++;
     }
}

int handle_key(int key, t_wfm *data)
{
    ft_printf("%d\n", key);


    if (key == 119 || key == 65362)
        data->shift_y -=10;
    if (key == 115 || key == 65364)
        data->shift_y +=10;
    if (key == 97 || key == 65361)
        data->shift_x -=10;
    if (key == 100 || key == 65363)
        data->shift_x +=10;
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    draw(data);
    return (0);
}

void    free_data(t_wfm *data)
{
    int i;

    i = 0;
    if (!data || !data->height)
        return ;
    if (data->z_matrix)
    {
        while (i < data->height)
        {
            free(data->z_matrix[i]);
            i++;
        }
        free(data->z_matrix);
    }
    if (data->mlx_ptr)
        free(data->mlx_ptr);
    if (data->win_ptr)
        free(data->win_ptr);
    free(data);
    data = NULL;
}

int main(int ac, char **av)
{
    t_wfm *data;
    int i;
    int j;

    data = (t_wfm *)malloc(sizeof(t_wfm));
    if (data == NULL)
        return (MALLOC_ERROR);
    read_file(av[1], data);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, 1000, 1000, "FDF");
    data->zoom = 20;
    draw(data);
	mlx_key_hook(data->win_ptr, handle_key, data);
	mlx_loop(data->mlx_ptr);
}
