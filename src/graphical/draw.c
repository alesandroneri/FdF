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
void isometric(float *x, float *y, int z)
{
    *x = (*x - *y) * cos(0.8);
    *y = (*x + *y) * sin(0.8) - z;
}

//void bresenham(float x, float y, float x1, float y1, t_fdf *data)//[1:1] [3:12]
void bresenham(float x, float y, float x1, float y1, t_fdf *data)//[1:1] [3:12]
{
    float x_step;
    float y_step;
    int max;
    int z;
    int z1;
    int starting_color;

    //z = data->z_matrix[(int)y][(int)x].value;
    //z1 = data->z_matrix[(int)y1][(int)x1].value;
    z = data->z_matrix[(int)(y * data->width + x)].value; // Acesso ao valor Z
	z1 = data->z_matrix[(int)(y1 * data->width + x1)].value; // Acesso ao valor Z1

    starting_color = 0;
    //zoom
    x *= data->zoom;
    y *= data->zoom;
    x1 *= data->zoom;
    y1 *= data->zoom;
    //color
    data->color = (z || z1) ? 0xe80c8c : 0xffffff;
    //starting_color = ft_atoi_base(data->z_matrix[(int)y][(int)x].hex, 16);
    //starting_color = ft_atoi_base(data->z_matrix[(int)(y * data->width + x)].hex); 
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
        mlx_pixel_put(data->mlx_ptr, data->win_ptr, x, y, data->color);
        x += x_step;
        y += y_step;
    }
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
