#include "fdf.h"

# define MALLOC_ERROR 1
# define READ_FILE_ERROR 1

int close_window(void *param)
{
    t_fdf *data = (t_fdf *)param; // Converte o ponteiro para o tipo correto
    mlx_destroy_window(data->mlx_ptr, data->win_ptr); // Destroi a janela
    free(data->z_matrix); // Libera a matriz de dados, se necessário
    free(data);           // Libera a struct data
    exit(0);              // Encerra o programa
}

int handle_key(int key, t_fdf *data)
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
    if (key == 65451) // Tecla '+'
        data->zoom += 1;
    if (key == 65453 && data->zoom > 1) // Tecla '-'
        data->zoom -= 1;
    // Fechar o programa
    if (key == 65307) // Tecla 'ESC'
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        free(data->z_matrix);
        exit(0);
    }
    mlx_clear_window(data->mlx_ptr, data->win_ptr);
    draw(data);
    return (0);
}
void    free_data(t_fdf *data)
{
    int i;

    i = 0;
    if (!data || !data->height)
        return ;
    if (data->z_matrix)
    {
        while (i < data->height)
        {
            free(data->z_matrix[i].hex);
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

// int main(int ac, char **av)
// {
//     t_fdf *data;
//     int i;
//     int j;

//     data = (t_fdf *)malloc(sizeof(t_fdf));
//     if (data == NULL)
//         return (MALLOC_ERROR);
//      data->z_matrix = NULL;
//      data->height = 0;
//      data->width = 0;
//      data->mlx_ptr = NULL;
//      data->win_ptr = NULL;
//     read_file(av[1], data);
//     i = 0;
//     while (i < data->height)
//     {
//         j = 0;
//         while (j < data->width)
//         {
//             ft_printf("%d ", data->z_matrix[i][j]);
//             j++;
//         }
//         ft_printf("\n");
//         i++;
//     }
//     free_data(data);
// }

int main(int ac, char **av)
{
    t_fdf *data;
    int i;
    int j;
    int win_width;
    int win_height;

    i = 0;
    j = 0;
    if (av[2] && av[3])
    {
        while (av[2][i] != '\0' && av[3][j] != '\0')
        {
            if (!ft_isdigit(av[2][i]) || !ft_isdigit(av[3][j]))
            {
                ft_printf("Invalid window!");
                return (0);
            }
            i++;
            j++;
        }
    }
    win_width = ft_atoi(av[2]);
    win_height = ft_atoi(av[3]);

    data = (t_fdf *)malloc(sizeof(t_fdf));
    if (data == NULL)
        return (MALLOC_ERROR);
    // data->z_matrix = NULL;
    // data->height = 0;
    // data->width = 0;
    // data->mlx_ptr = NULL;
    // data->win_ptr = NULL;
    read_file(av[1], data);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, win_width, win_height, "FDF");
    data->zoom = 20;

    //bresenham(10, 10, 600, 300, data);
    draw(data);
    mlx_hook(data->win_ptr, 17, 0, close_window, data); // Evento do botão "X"
	mlx_key_hook(data->win_ptr, handle_key, data); // Evento de teclado
	mlx_loop(data->mlx_ptr);
    free(data);
}