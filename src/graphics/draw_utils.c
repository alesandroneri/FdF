/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:21:32 by aneri-da          #+#    #+#             */
/*   Updated: 2024/12/22 16:21:35 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../fdf.h"

int	maximum(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

float	mod(float i)
{
	if (i < 0)
		return (-i);
	return (i);
}

void	initial_values(t_coordinates *coordinates, t_fdf *data)
{
	coordinates->z = data->z_matrix[(int)(coordinates->y * data->width
			+ coordinates->x)].z_value;
	coordinates->z1 = data->z_matrix[(int)(coordinates->y1 * data->width
			+ coordinates->x1)].z_value;
	coordinates->color = ft_atoi_base(data->z_matrix[(int)(coordinates->y
				* data->width + coordinates->x)].color_hex, 16);
}

void	isometric(float *x, float *y, int z, t_graphics *graphics)
{
	float	previous_x;
	float	previous_y;
	float	rotated_y;
	float	rotated_z;
	float	rotated_x;

	previous_x = *x;
	previous_y = *y;
	z *= graphics->depth_factor;
	rotated_y = previous_y * cos(graphics->angle_x) - z
		* sin(graphics->angle_x);
	rotated_z = previous_y * sin(graphics->angle_x) + z
		* cos(graphics->angle_x);
	rotated_x = previous_x * cos(graphics->angle_y) + rotated_z
		* sin(graphics->angle_y);
	rotated_z = -previous_x * sin(graphics->angle_y) + rotated_z
		* cos(graphics->angle_y);
	*x = rotated_x;
	*y = rotated_y;
}

void	put_pixel(t_coordinates *coordinates, t_gen_res *gen_data)
{
	int	pixel;

	pixel = 0;
	if ((coordinates->x >= 0 && (coordinates->x < gen_data->data->win_width))
		&& (coordinates->y >= 0
			&& (coordinates->y < gen_data->data->win_height)))
	{
		pixel = ((int)coordinates->y * gen_data->img->line_length
				+ (int)coordinates->x * (gen_data->img->bpp / 8));
		*(int *)(gen_data->img->img_data + pixel) = coordinates->color;
	}
}
