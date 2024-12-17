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
        data->graphics.shift_y -=10;
    if (key == 115 || key == 65364)
        data->graphics.shift_y +=10;
    if (key == 97 || key == 65361)
        data->graphics.shift_x -=10;
    if (key == 100 || key == 65363)
        data->graphics.shift_x +=10;
    if (key == 65451 && data->graphics.zoom < 21) // Tecla '+'
        data->graphics.zoom += 1;
    if (key == 65453 && data->graphics.zoom > 3) // Tecla '-'
        data->graphics.zoom -= 1;
    if (key == 65431)
        data->graphics.depth_factor += 0.1;
    if (key == 65433)
        data->graphics.depth_factor -= 0.1;
    if (key == 120)
    {
        data->graphics.angle_x += 0.1;
        printf("angulo_x: %f\n", data->graphics.angle_x);
    }
    if (key == 121)
    {
        data->graphics.angle_y += 0.1;
        printf("angulo_y: %f\n", data->graphics.angle_y);
    }
    if (key == 122)
    {
        data->graphics.angle_z += 0.1;
        printf("angulo_z: %f\n", data->graphics.angle_z);
    }
    if (key == 105)
    {
        data->graphics.isometric_angle += 0.1;
        printf("angulo_isometrico: %f\n", data->graphics.isometric_angle);
    }
    // Fechar o programa
    if (key == 65307) // Tecla 'ESC'
    {
        mlx_destroy_window(data->mlx_ptr, data->win_ptr);
        free(data->z_matrix);
        exit(0);
    }
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
    float map_center_x;
    float map_center_y;

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
    // data->win_width = ft_atoi(av[2]);
    // data->win_height = ft_atoi(av[3]);

    data = (t_fdf *)malloc(sizeof(t_fdf));
    data->win_width = ft_atoi(av[2]);
    data->win_height = ft_atoi(av[3]);
    if (data == NULL)
        return (MALLOC_ERROR);

    read_file(av[1], data);
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->win_width, data->win_height, "FDF");
    data->img.img = mlx_new_image(data->mlx_ptr, data->width, data->height);
    data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bpp, &data->img.line_length, &data->img.endian);
    data->graphics.zoom = 4;
    data->graphics.angle_x = 0.1;
    //data->angle_x = 0;
    data->graphics.angle_y = 0.3;
    //data->angle_y = 0;
    //data->angle_z = M_PI / 6;
    data->graphics.angle_z = 5.29;
    data->graphics.isometric_angle = 0.6;
    //data->isometric_angle = 1;
    data->graphics.depth_factor = 0.3;
    map_center_x = (data->width - 1) * (data->graphics.zoom / 50);
    map_center_y = (data->height - 1) * (data->graphics.zoom / 50);
    data->graphics.shift_x = (data->win_width / 2) - map_center_x;
    data->graphics.shift_y = (data->win_height / 2) - map_center_y;
    
    draw(data);
    mlx_hook(data->win_ptr, 17, 0, close_window, data); // Evento do botão "X"
	mlx_key_hook(data->win_ptr, handle_key, data); // Evento de teclado
	mlx_loop(data->mlx_ptr);
    free(data);
}