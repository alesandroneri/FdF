#include "../../fdf.h"

// Função para centralizar o mapa
void center_map(t_coordinates *coordinates, t_gen_res *gen_data)
{   
    //Centralizar o mapa
    coordinates->x -= (gen_data->data->width - 1) * (gen_data->graphics->zoom / 2.0);
	coordinates->y -= (gen_data->data->height - 1) * (gen_data->graphics->zoom / 2.0);
	coordinates->x1 -= (gen_data->data->width - 1) * (gen_data->graphics->zoom / 2.0);
	coordinates->y1 -= (gen_data->data->height - 1) * (gen_data->graphics->zoom / 2.0);
}

// Função para o zoom
void zoom(t_coordinates *coordinates, t_graphics *graphics)
{
    coordinates->x *= graphics->zoom;
    coordinates->y *= graphics->zoom;
    coordinates->x1 *= graphics->zoom;
    coordinates->y1 *= graphics->zoom;
}

// Função para mover o mapa
void shift(t_coordinates *coordinates, t_graphics *graphics)
{
    // Aplicar o shift
    coordinates->x += graphics->shift_x;
	coordinates->y += graphics->shift_y;
	coordinates->x1 += graphics->shift_x;
	coordinates->y1 += graphics->shift_y;
}