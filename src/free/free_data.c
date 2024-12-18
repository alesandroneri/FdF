#include "../../fdf.h"

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