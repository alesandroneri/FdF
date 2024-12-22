/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:00:43 by aneri-da          #+#    #+#             */
/*   Updated: 2024/12/22 17:00:46 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "keys.h"

int	movement_keys(int key, t_gen_res *gen_data)
{
	if (key == KEYCAP_A)
		gen_data->graphics->shift_x -= 10;
	else if (key == KEYCAP_D)
		gen_data->graphics->shift_x += 10;
	else if (key == KEYCAP_W)
		gen_data->graphics->shift_y -= 10;
	else if (key == KEYCAP_S)
		gen_data->graphics->shift_y += 10;
	else
		return (0);
	return (1);
}

int	zoom_keys(int key, t_gen_res *gen_data)
{
	if (key == KEYCAP_PLUS_SIGN && gen_data->graphics->zoom < 50)
		gen_data->graphics->zoom += 1;
	else if (key == KEYCAP_MINUS_SIGN && gen_data->graphics->zoom > 3)
		gen_data->graphics->zoom -= 1;
	else
		return (0);
	return (1);
}

int	depth_keys(int key, t_gen_res *gen_data)
{
	if (key == KEYCAP_NB_8)
		gen_data->graphics->depth_factor += 0.1f;
	else if (key == KEYCAP_NB_2)
		gen_data->graphics->depth_factor -= 0.1f;
	else
		return (0);
	return (1);
}

int	rotation_keys(int key, t_gen_res *gen_data)
{
	if (key == KEYCAP_ARROW_UP)
		gen_data->graphics->angle_x += 0.1f;
	else if (key == KEYCAP_ARROW_DOWN)
		gen_data->graphics->angle_x -= 0.1f;
	else if (key == KEYCAP_ARROW_RIGHT)
		gen_data->graphics->angle_y += 0.1f;
	else if (key == KEYCAP_ARROW_LEFT)
		gen_data->graphics->angle_y -= 0.1f;
	else
		return (0);
	return (1);
}
