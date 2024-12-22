/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics_features.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:59:13 by aneri-da          #+#    #+#             */
/*   Updated: 2024/12/22 16:59:16 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../fdf.h"

void	center_map(t_coordinates *coordinates, t_gen_res *gen_data)
{
	coordinates->x -= (gen_data->data->width - 1) * (gen_data->graphics->zoom
			/ 2.0);
	coordinates->y -= (gen_data->data->height - 1) * (gen_data->graphics->zoom
			/ 2.0);
	coordinates->x1 -= (gen_data->data->width - 1) * (gen_data->graphics->zoom
			/ 2.0);
	coordinates->y1 -= (gen_data->data->height - 1) * (gen_data->graphics->zoom
			/ 2.0);
}

void	zoom(t_coordinates *coordinates, t_graphics *graphics)
{
	coordinates->x *= graphics->zoom;
	coordinates->y *= graphics->zoom;
	coordinates->x1 *= graphics->zoom;
	coordinates->y1 *= graphics->zoom;
}

void	shift(t_coordinates *coordinates, t_graphics *graphics)
{
	coordinates->x += graphics->shift_x;
	coordinates->y += graphics->shift_y;
	coordinates->x1 += graphics->shift_x;
	coordinates->y1 += graphics->shift_y;
}
