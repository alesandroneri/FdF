/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   panel_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:59:30 by aneri-da          #+#    #+#             */
/*   Updated: 2024/12/22 16:59:34 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../fdf.h"

int	get_text_size(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	i = i * 7;
	return (i);
}

void	draw_text(t_coordinates *coordinates, char *text, char *value,
		t_gen_res *gen_data)
{
	int	name_size;

	name_size = get_text_size(text);
	mlx_string_put(gen_data->data->mlx_ptr, gen_data->data->win_ptr,
		coordinates->x, coordinates->y, 0xFFFFFF, text);
	mlx_string_put(gen_data->data->mlx_ptr, gen_data->data->win_ptr,
		coordinates->x + name_size, coordinates->y, 0xFFFFFF, value);
	coordinates->y += 20;
	free(value);
}

void	draw_panel_info(t_gen_res *gen_data)
{
	t_coordinates	point;

	point.x = 10;
	point.y = 10;
	draw_text(&point, "Shift X: ", ft_itoa(gen_data->graphics->shift_x),
		gen_data);
	draw_text(&point, "Shift Y: ", ft_itoa(gen_data->graphics->shift_y),
		gen_data);
	draw_text(&point, "Rotation X: ", ft_itoa(gen_data->graphics->angle_x),
		gen_data);
	draw_text(&point, "Rotation Y: ", ft_itoa(gen_data->graphics->angle_y),
		gen_data);
	draw_text(&point, "Relief: ", ft_itoa(gen_data->graphics->depth_factor),
		gen_data);
	draw_text(&point, "Zoom: ", ft_itoa(gen_data->graphics->zoom), gen_data);
}
