#include "../../fdf.h"

static int maximum(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}
static float mod(float i)
{
    if (i < 0)
        return (-i);
    return (i);
}
// Função que pega os valores iniciais
static void initial_values(t_coordinates *coordinates, t_fdf *data)
{
    // Acessa os valores iniciais da matriz z
    coordinates->z = data->z_matrix[(int)(((coordinates->y) * data->width) + coordinates->x)].z_value;
    coordinates->z1 = data->z_matrix[(int)(((coordinates->y1) * data->width) + coordinates->x1)].z_value;
    // Acessar a cor inicial
	coordinates->color = ft_atoi_base(data->z_matrix[(int)(((coordinates->y) * data->width) + (coordinates->x))].color_hex, 16);
}

// Função para centralizar o mapa
void center_map(t_coordinates *coordinates, t_gen_res *gen_data)
{   
    // Centralizar o mapa
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

// Função para realizar uma projeção isométrica do mapa
static void	isometric(float *x, float *y, int z, t_graphics *graphics)
{
	float	previous_x;
	float	previous_y;
	float	rotated_y;
	float	rotated_z;
	float	rotated_x;

	previous_x = *x;
	previous_y = *y;
	z *= graphics->depth_factor;
	rotated_y = previous_y * cos(graphics->angle_x) - z * sin(graphics->angle_x);
	rotated_z = previous_y * sin(graphics->angle_x) + z * cos(graphics->angle_x);
	rotated_x = previous_x * cos(graphics->angle_y) + rotated_z
		* sin(graphics->angle_y);
	rotated_z = -previous_x * sin(graphics->angle_y) + rotated_z
		* cos(graphics->angle_y);
	*x = rotated_x;
	*y = rotated_y;
}

// Função que coloca pixels
static void    put_pixel(t_coordinates *coordinates, t_gen_res *gen_data)
{
    int pixel;

    pixel = 0;
    if (coordinates->x >= 0 && coordinates->x < gen_data->data->win_width && coordinates->y >= 0 && coordinates->y < gen_data->data->win_height)
    { 
        pixel = (((int)coordinates->y * gen_data->img->line_length) + ((int)coordinates->x * (gen_data->img->bpp / 8)));
        *(unsigned int *)(gen_data->img->img_data + pixel) = coordinates->color;
    }

}
void bresenham(t_coordinates *coordinates, t_gen_res *gen_data)
{
    float x_step;
    float y_step;
    int max;

    max = 0;
    x_step = 0;
    y_step = 0;
    coordinates->z = 0;
    coordinates->z1 = 0;
    coordinates->color = 0;
    initial_values(coordinates, gen_data->data);
    zoom(coordinates, gen_data->graphics);
    center_map(coordinates, gen_data);
    isometric(&coordinates->x, &coordinates->y, coordinates->z, gen_data->graphics);
    isometric(&coordinates->x1, &coordinates->y1, coordinates->z1, gen_data->graphics);
    shift(coordinates, gen_data->graphics);
    x_step = coordinates->x1 - coordinates->x;
    y_step = coordinates->y1 - coordinates->y;
    max = maximum(mod(x_step), mod(y_step));
    x_step /= max;
    y_step /= max;
    while ((int)(coordinates->x - coordinates->x1) || (int)(coordinates->y - coordinates->y1))
    {
        put_pixel(coordinates, gen_data);
        //mlx_pixel_put(gen_data->data->mlx_ptr, gen_data->data->win_ptr, coordinates->x, coordinates->y, coordinates->color);
        coordinates->x += x_step;
        coordinates->y += y_step;
    }
    mlx_put_image_to_window(gen_data->data->mlx_ptr, gen_data->data->win_ptr, gen_data->img->img_ptr, 0, 0);
}


/*
Função que desenha linhas entre os pontos.
*/

 void draw(t_gen_res *gen_data)
 {
    t_coordinates coordinates;

     coordinates.y = 0;
     while(coordinates.y < gen_data->data->height)
     {
         coordinates.x = 0;
         while(coordinates.x < gen_data->data->width)
         {
            if (coordinates.x < gen_data->data->width - 1)
                bresenham(&coordinates, gen_data);
            if (coordinates.y < gen_data->data->height - 1)
                bresenham(&coordinates, gen_data);
             coordinates.x++;
         }
         coordinates.y++;
     }
}
