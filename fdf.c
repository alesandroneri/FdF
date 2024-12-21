#include "fdf.h"

# define MAX_WIN_WIDTH 1920
# define MAX_WIN_HEIGHT 1080
# define MIN_WIN_WIDTH 800
# define MIN_WIN_HEIGHT 600


// Função para inicializar a imagem
void setup_image(t_gen_res *gen_data)
{
    ft_printf("START - setup_image\n");
    gen_data->img->img_ptr= mlx_new_image(gen_data->data->mlx_ptr, gen_data->data->win_width, gen_data->data->win_height);
    if (!gen_data->img->img_ptr)
        exit(0);
    gen_data->img->img_data = mlx_get_data_addr(gen_data->img->img_ptr, &gen_data->img->bpp, &gen_data->img->line_length, &gen_data->img->endian);
    if (!gen_data->img->img_data)
        exit(0);
    draw(gen_data);
    ft_printf("END - setup_image\n");
}


// Função para inicializar as variáveis
void setup_variables(t_gen_res *gen_data)
{
    ft_printf("START - setup_variables\n");
    float map_center_x;
    float map_center_y;

    gen_data->graphics->zoom = 4;
    gen_data->graphics->angle_x = 0.2;
    gen_data->graphics->angle_y = 0.2;
    gen_data->graphics->depth_factor = 0.8;
    map_center_x = (gen_data->data->width - 1) * (gen_data->graphics->zoom / 50);
    map_center_y = (gen_data->data->height - 1) * (gen_data->graphics->zoom / 50);
    gen_data->graphics->shift_x = (gen_data->data->win_width / 2) - map_center_x;
    gen_data->graphics->shift_y = (gen_data->data->win_height / 2) - map_center_y;
    ft_printf("END - setup_variables\n");
}

// Função para inicializar o server
int init(t_gen_res *gen_data)
{
    ft_printf("START - init\n");
    gen_data->data->mlx_ptr = mlx_init();
    if (!gen_data->data->mlx_ptr)
        return (0);
    /*if (!ft_isdigit(av2) || !ft_isdigit(av3))
    {
        ft_putendl_fd("Invalid window!", 2);
        return (0);
    }*/

    gen_data->data->win_width = 1920;
    gen_data->data->win_height = 1080;
    gen_data->data->win_ptr = NULL;
    mlx_get_screen_size(gen_data->data->mlx_ptr, &gen_data->data->win_width, &gen_data->data->win_height);
    if (gen_data->data->win_width < 0 || gen_data->data->win_height < 0)
        return (0);
    gen_data->data->win_ptr = mlx_new_window(gen_data->data->mlx_ptr,
    gen_data->data->win_width, gen_data->data->win_height, "FDF");
    if (!gen_data->data->win_ptr)
        return (0);
    setup_variables(gen_data);
    ft_printf("END - init\n");
    return (1);
}


// Função para mallocar as structs
int malloc_structs_resources(t_gen_res *gen_data)
{
    ft_printf("START - malloc_structs_resources\n");
    gen_data->data = (t_fdf *)malloc(sizeof(t_fdf));
    if (!gen_data->data)
    {
        free_resources(gen_data);
        return (0);
    }
    gen_data->graphics = (t_graphics *)malloc(sizeof(t_graphics));
    if (!gen_data->graphics)
    {
        free_resources(gen_data);
        return (0);
    }
    gen_data->img = (t_img *)malloc(sizeof(t_img));
    if (!gen_data->img)
    {
        free_resources(gen_data);
        return (0);
    }
    ft_printf("END - malloc_structs_resources\n");
    return (1);
}

int main(int ac, char **av)
{
    t_gen_res gen_data;
    //int i;
    //int j;

    if (ac < 2 || ac > 4)
    {
        ft_putendl_fd("Invalid number of arguments!", 2);
        return (0);
    }
    // i = -1;
    // j = -1;
    // if (av[2] && av[3])
    // {
    //     while (av[2][i++] != '\0' && av[3][j++] != '\0')
    //     {
    //         if (!ft_isdigit(av[2][i]) || !ft_isdigit(av[3][j]))
    //         {
    //             ft_putendl_fd("Invalid window!", 2);
    //             return (0);
    //         }
    //     }
    // }

    if (!malloc_structs_resources(&gen_data))
    {
        ft_putendl_fd("Memory allocation failed!", 2);
        return (0);
    }
    read_file(av[1], gen_data.data);
    if (init(&gen_data))
    {
        setup_image(&gen_data);
        setup_hooks(&gen_data);
        mlx_loop(gen_data.data->mlx_ptr);
    }
    free_resources(&gen_data);
    free_server(&gen_data);
}