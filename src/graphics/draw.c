#include "../../fdf.h"

// Função para pegar o valor máximo
static int maximum(int a, int b)
{
    if (a > b)
        return (a);
    return (b);
}

// Função para pegar o modulo do número
static float mod(float i)
{
    if (i < 0)
        return (-i);
    return (i);
}

void reset_image(t_fdf *data, t_img *img) 
{
    ft_printf("START - reset_image\n");
    // if (data->mlx_ptr && img->img_ptr)
    mlx_destroy_image(data->mlx_ptr, img->img_ptr); // remover isso aqui porque a imagem nao foi destruida
    img->img_ptr = mlx_new_image(data->mlx_ptr, data->win_width, data->win_height);
    img->img_data = mlx_get_data_addr(img->img_ptr, &img->bpp, &img->line_length, &img->endian);
    ft_printf("END - reset_image\n");
}
// Função que pega os valores iniciais
static void initial_values(t_coordinates *coordinates, t_fdf *data)
{
    ft_printf("START - initial_values\n");
    // Acessa os valores iniciais da matriz z
    coordinates->z = data->z_matrix[(int)(coordinates->y * data->width + coordinates->x)].z_value;
    coordinates->z1 = data->z_matrix[(int)(coordinates->y1 * data->width + coordinates->x1)].z_value;
    // Acessar a cor inicial
    //coordinates->color = 0xffffff;
	coordinates->color = ft_atoi_base(data->z_matrix[(int)(coordinates->y * data->width + coordinates->x)].color_hex, 16);
    // coordinates->color = ft_atoi_hexa(data->z_matrix[(int)(((coordinates->y) * data->width) + (coordinates->x))].color_hex);
    ft_printf("END - initial_values\n");
}

// Função para centralizar o mapa
void center_map(t_coordinates *coordinates, t_gen_res *gen_data)
{   
    ft_printf("START - center_map\n");
    printf("Width: %d, Height: %d, Zoom: %d\n", 
              gen_data->data->width, 
              gen_data->data->height, 
              gen_data->graphics->zoom);
    ft_printf("Antes do deslocamento:\n");
    printf("x: %f, y: %f, x1: %f, y1: %f\n", 
              coordinates->x, 
              coordinates->y, 
              coordinates->x1, 
              coordinates->y1);
    float offset_x = (gen_data->data->width - 1) * gen_data->graphics->zoom / 2.0;
    float offset_y = (gen_data->data->height - 1) * gen_data->graphics->zoom / 2.0;
    printf("Offset X: %f, Offset Y: %f\n", offset_x, offset_y);
    coordinates->x -= offset_x;
    coordinates->y -= offset_y;
    coordinates->x1 -= offset_x;
    coordinates->y1 -= offset_y;
    // Centralizar o mapa
    // coordinates->x -= (gen_data->data->width - 1) * gen_data->graphics->zoom / 2.0;
	// coordinates->y -= (gen_data->data->height - 1) * gen_data->graphics->zoom / 2.0;
	// coordinates->x1 -= (gen_data->data->width - 1) * gen_data->graphics->zoom / 2.0;
	// coordinates->y1 -= (gen_data->data->height - 1) * gen_data->graphics->zoom / 2.0;
    ft_printf("Depois do deslocamento:\n");
    printf("x: %f, y: %f, x1: %f, y1: %f\n", 
              coordinates->x, 
              coordinates->y, 
              coordinates->x1, 
              coordinates->y1);
    ft_printf("END - center_map\n");
}

// Função para o zoom
void zoom(t_coordinates *coordinates, t_graphics *graphics)
{
    ft_printf("START - zoom\n");
    coordinates->x *= graphics->zoom;
    coordinates->y *= graphics->zoom;
    coordinates->x1 *= graphics->zoom;
    coordinates->y1 *= graphics->zoom;
    ft_printf("END - zoom\n");
}

// Função para mover o mapa
void shift(t_coordinates *coordinates, t_graphics *graphics)
{
    ft_printf("START - shift\n");
    // Aplicar o shift
    coordinates->x += graphics->shift_x;
	coordinates->y += graphics->shift_y;
	coordinates->x1 += graphics->shift_x;
	coordinates->y1 += graphics->shift_y;
    ft_printf("END - shift\n");
}

// Função para realizar uma projeção isométrica do mapa
static void	isometric(float *x, float *y, int z, t_graphics *graphics)
{
    ft_printf("START - isometric\n");
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
    ft_printf("START - isometric\n");
}

// Função que coloca pixels
static void    put_pixel(t_coordinates *coordinates, t_gen_res *gen_data)
{
    ft_printf("START - put_pixel\n");
    int pixel;

    pixel = 0;
    if ((coordinates->x >= 0 && (coordinates->x < gen_data->data->win_width)) && (coordinates->y >= 0 && (coordinates->y < gen_data->data->win_height)))
    { 
        pixel = (coordinates->y * gen_data->img->line_length + coordinates->x * (gen_data->img->bpp / 8));
        *(int *)(gen_data->img->img_data + pixel) = coordinates->color;
    }
    ft_printf("END - put_pixel\n");

}

void setup_coordinates(t_coordinates coordinates, t_gen_res *gen_data)
{
    if (coordinates.x < gen_data->data->width - 1)
    {
        coordinates.x1 = coordinates.x + 1;
        coordinates.y1 = coordinates.y;
        bresenham(coordinates, gen_data);
    }
    if (coordinates.y < gen_data->data->height - 1)
    {
        coordinates.x1 = coordinates.x;
        coordinates.y1 = coordinates.y + 1;
        bresenham(coordinates, gen_data);
    }
}
void bresenham_line(t_coordinates *coordinates, t_gen_res *gen_data)
{
    float x_step;
    float y_step;

    x_step = 0;
    y_step = 0;
    ft_printf("START - bresenham_line\n");
    int max;

    max = 0;
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
    ft_printf("END - bresenham_line\n");
}

// Função do algoritmo de bresenham para fazer linhas
void bresenham(t_coordinates coordinates, t_gen_res *gen_data)
{
    ft_printf("START - bresenham\n");
    // float x_step;
    // float y_step;

    // x_step = 0;
    // y_step = 0;
    coordinates.z = 0;
    coordinates.z1 = 0;
    coordinates.color = 0;
    initial_values(&coordinates, gen_data->data);
    printf("Antes do zoom: x=%f, y=%f, x1=%f, y1=%f\n", coordinates.x, coordinates.y, coordinates.x1, coordinates.y1);
    zoom(&coordinates, gen_data->graphics);
    printf("Depois do zoom: x=%f, y=%f, x1=%f, y1=%f\n", coordinates.x, coordinates.y, coordinates.x1, coordinates.y1);
    printf("Antes do center_map: x=%f, y=%f, x1=%f, y1=%f\n", coordinates.x, coordinates.y, coordinates.x1, coordinates.y1);
    center_map(&coordinates, gen_data);
    printf("Depois do center_map: x=%f, y=%f, x1=%f, y1=%f\n", coordinates.x, coordinates.y, coordinates.x1, coordinates.y1);
    isometric(&coordinates.x, &coordinates.y, coordinates.z, gen_data->graphics);
    isometric(&coordinates.x1, &coordinates.y1, coordinates.z1, gen_data->graphics);
    shift(&coordinates, gen_data->graphics);
    bresenham_line(&coordinates, gen_data);
    ft_printf("END - bresenham\n");
}
/*
Função que desenha linhas entre os pontos.
*/
int get_text_size(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    i = i * 7;
    return (i);
}

static void draw_text(t_coordinates *coordinates, char *text, char *value, t_gen_res *gen_data)
{
    int name_size;

    name_size = get_text_size(text);
    mlx_string_put(gen_data->data->mlx_ptr, gen_data->data->win_ptr, coordinates->x, coordinates->y, 0xFFFFFF, text);
    mlx_string_put(gen_data->data->mlx_ptr, gen_data->data->win_ptr, coordinates->x + name_size, coordinates->y, 0xFFFFFF, value);
    coordinates->y += 20;
    free(value);
}

void    draw_panel_info(t_gen_res *gen_data)
{
    t_coordinates point;
    point.x = 10;
    point.y = 10;

    draw_text(&point, "Shift X: ", ft_itoa(gen_data->graphics->shift_x), gen_data);
    draw_text(&point, "Shift Y: ", ft_itoa(gen_data->graphics->shift_y), gen_data);
    draw_text(&point, "Rotation X: ", ft_itoa(gen_data->graphics->angle_x), gen_data);
    draw_text(&point, "Rotation Y: ", ft_itoa(gen_data->graphics->angle_y), gen_data);
    draw_text(&point, "Relief: ", ft_itoa(gen_data->graphics->depth_factor), gen_data);
    draw_text(&point, "Zoom: ", ft_itoa(gen_data->graphics->zoom), gen_data);

}

 void draw(t_gen_res *gen_data)
 {
    ft_printf("START - draw\n");
    reset_image(gen_data->data, gen_data->img);
    t_coordinates coordinates;

    coordinates.y = 0;
    while(coordinates.y < gen_data->data->height)
    {
        coordinates.x = 0;
        while(coordinates.x < gen_data->data->width)
        {
            setup_coordinates(coordinates, gen_data);
            coordinates.x++;
        }
        coordinates.y++;
    }
    mlx_put_image_to_window(gen_data->data->mlx_ptr, gen_data->data->win_ptr, gen_data->img->img_ptr, 0, 0);
    
    draw_panel_info(gen_data);
    ft_printf("END - draw\n");
}
