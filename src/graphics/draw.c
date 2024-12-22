/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:22:05 by aneri-da          #+#    #+#             */
/*   Updated: 2024/12/22 16:22:09 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../fdf.h"

static void	reset_image(t_fdf *data, t_img *img)
{
	if (data->mlx_ptr && img->img_ptr)
		mlx_destroy_image(data->mlx_ptr, img->img_ptr);
	img->img_ptr = mlx_new_image(data->mlx_ptr, data->win_width,
			data->win_height);
	img->img_data = mlx_get_data_addr(img->img_ptr, &img->bpp,
			&img->line_length, &img->endian);
}

static void	bresenham_line(t_coordinates coordinates, t_gen_res *gen_data)
{
	float	x_step;
	float	y_step;
	int		max;

	x_step = 0;
	y_step = 0;
	max = 0;
	x_step = coordinates.x1 - coordinates.x;
	y_step = coordinates.y1 - coordinates.y;
	max = maximum(mod(x_step), mod(y_step));
	x_step /= max;
	y_step /= max;
	while ((int)(coordinates.x - coordinates.x1) || (int)(coordinates.y
			- coordinates.y1))
	{
		put_pixel(&coordinates, gen_data);
		coordinates.x += x_step;
		coordinates.y += y_step;
	}
}

static void	bresenham(t_coordinates coordinates, t_gen_res *gen_data)
{
	coordinates.z = 0;
	coordinates.z1 = 0;
	coordinates.color = 0;
	initial_values(&coordinates, gen_data->data);
	zoom(&coordinates, gen_data->graphics);
	center_map(&coordinates, gen_data);
	isometric(&coordinates.x, &coordinates.y, coordinates.z,
		gen_data->graphics);
	isometric(&coordinates.x1, &coordinates.y1, coordinates.z1,
		gen_data->graphics);
	shift(&coordinates, gen_data->graphics);
	bresenham_line(coordinates, gen_data);
}

static void	setup_coordinates(t_coordinates coordinates, t_gen_res *gen_data)
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

void	draw(t_gen_res *gen_data)
{
	t_coordinates	coordinates;

	reset_image(gen_data->data, gen_data->img);
	coordinates.y = 0;
	while (coordinates.y < gen_data->data->height)
	{
		coordinates.x = 0;
		while (coordinates.x < gen_data->data->width)
		{
			setup_coordinates(coordinates, gen_data);
			coordinates.x++;
		}
		coordinates.y++;
	}
	mlx_put_image_to_window(gen_data->data->mlx_ptr, gen_data->data->win_ptr,
		gen_data->img->img_ptr, 0, 0);
	draw_panel_info(gen_data);
}
