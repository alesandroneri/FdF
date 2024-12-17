#include "../../fdf.h"

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

void isometric(float *x, float *y, int z, t_fdf *data)
{
    float prev_x;
    float prev_y;
    float adjusted_z;

    // Salvar os valores originais de x, y e z
    prev_x = *x;
    prev_y = *y;
    adjusted_z = z * (data->graphics.depth_factor);

    // 1. Rotação em torno do eixo X
    *y = prev_y * cos(data->graphics.angle_x) - adjusted_z * sin(data->graphics.angle_x);
    adjusted_z = prev_y * sin(data->graphics.angle_x) + adjusted_z * cos(data->graphics.angle_x);

    // 2. Rotação em torno do eixo Y
    *x = prev_x * cos(data->graphics.angle_y) + adjusted_z * sin(data->graphics.angle_y);
    adjusted_z = -prev_x * sin(data->graphics.angle_y) + adjusted_z * cos(data->graphics.angle_y);

    // 3. Rotação em torno do eixo Z
    prev_x = *x;
    prev_y = *y;
    *x = prev_x * cos(data->graphics.angle_z) - prev_y * sin(data->graphics.angle_z);
    *y = prev_x * sin(data->graphics.angle_z) + prev_y * cos(data->graphics.angle_z);

    // 4. Projeção Isométrica (transformação 2D)
    prev_x = *x;
    prev_y = *y;
    *x = (prev_x - prev_y) * cos(data->graphics.isometric_angle);
    *y = (prev_x + prev_y) * sin(data->graphics.isometric_angle) - adjusted_z; // Considera a profundidade Z

    // 5. Escalonamento para ajuste visual
    *x *= data->graphics.zoom;
    *y *= data->graphics.zoom;

    // 6. Translação (movimento da projeção para o centro da tela)
    *x += data->graphics.shift_x;
    *y += data->graphics.shift_y;
}

void    put_pixel(t_fdf *data, int x, int y, int color)
{
    int pixel;

    pixel = 0;
    if (x >= 0 && x < data->win_width && y >= 0 && y < data->win_height)
    { 
        pixel = (((int)y * data->img.line_length) + ((int)x * (data->img.bpp / 8)));
        *(unsigned int *)(data->img.addr + pixel) = color;
    }

}
void bresenham(float x, float y, float x1, float y1, t_fdf *data)//[1:1] [3:12]
{
    float x_step;
    float y_step;
    int max;
    int z;
    int z1;
    int starting_color;

    z = data->z_matrix[(int)(y * data->width + x)].value; // Acesso ao valor Z
	z1 = data->z_matrix[(int)(y1 * data->width + x1)].value; // Acesso ao valor Z1

    //starting_color = 0;
    //zoom
    x *= data->graphics.zoom;
    y *= data->graphics.zoom;
    x1 *= data->graphics.zoom;
    y1 *= data->graphics.zoom;

    //center of map
    x -= (data->width - 1) * (data->graphics.zoom / 2.0);
	y -= (data->height - 1) * (data->graphics.zoom / 2.0);
	x1 -= (data->width - 1) * (data->graphics.zoom / 2.0);
	y1 -= (data->height - 1) * (data->graphics.zoom / 2.0);

    //color
    data->graphics.color = (z || z1) ? 0xe80c8c : 0xffffff;
    //starting_color = ft_atoi_hexa(data->z_matrix[(int)(y * data->width + x)].hex); 
    //3D
    isometric(&x, &y, z, data);
    isometric(&x1, &y1, z1, data);
    x_step = x1 - x;
    y_step = y1 - y;
    max = maximum(mod(x_step), mod(y_step));
    x_step /= max;
    y_step /= max;
    while ((int)(x - x1) || (int)(y - y1))
    {
        put_pixel(data, x, y, ft_atoi_base(data->graphics.color, 16));
        //mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->graphics.color);
        //mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, starting_color);
        x += x_step;
        y += y_step;
    }
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);

}
/*
Função que desenha linhas entre os pontos.
*/

 void draw(t_fdf *data)
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
