#include "../../fdf.h"

// Função para liberar a matriz
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
            free(data->z_matrix[i].color_hex);
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

// Função para liberar os recursos das structs
void free_resources(t_gen_res *gen_data)
{
    if (gen_data->graphics)
        free(gen_data->graphics);
    if (gen_data->img)
        free(gen_data->img);
    if (gen_data->data)
        free(gen_data->data);
}

// Função para liberar o server, janela, display e imagem
void free_server(t_gen_res *gen_data)
{
    if (!gen_data->data)
        return ;
    // Libera o display
    if (gen_data->data->mlx_ptr)
    {
        mlx_destroy_display(gen_data->data->mlx_ptr);
        free(gen_data->data->mlx_ptr);
        gen_data->data->mlx_ptr = NULL;
    }
    // Libera a janela 
    if (gen_data->data->win_ptr)
    {
        mlx_destroy_window(gen_data->data->mlx_ptr, gen_data->data->win_ptr);
        free(gen_data->data->win_ptr);
        gen_data->data->win_ptr = NULL;
    }
    if (gen_data->img->img_data)
    {
        mlx_destroy_image(gen_data->data->mlx_ptr, gen_data->img->img_data);
        free(gen_data->img->img_data);
        gen_data->img->img_data = NULL;
    }
    // Libera os dados
    if (gen_data->data)
        free(gen_data->data);
}
