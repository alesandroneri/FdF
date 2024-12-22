/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 17:00:13 by aneri-da          #+#    #+#             */
/*   Updated: 2024/12/22 17:00:20 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../fdf.h"
#include "keys.h"

static int	handle_keys(int key, t_gen_res *gen_data)
{
	movement_keys(key, gen_data);
	zoom_keys(key, gen_data);
	depth_keys(key, gen_data);
	rotation_keys(key, gen_data);
	if (key == KEYCAP_ESC)
	{
		mlx_loop_end(gen_data->data->mlx_ptr);
		return (0);
	}
	draw(gen_data);
	return (0);
}

static int	close_button(t_gen_res *gen_data)
{
	mlx_loop_end(gen_data->data->mlx_ptr);
	return (0);
}

void	setup_hooks(t_gen_res *gen_data)
{
	mlx_hook(gen_data->data->win_ptr, 17, 0, close_button, gen_data);
	mlx_key_hook(gen_data->data->win_ptr, handle_keys, gen_data);
	mlx_hook(gen_data->data->win_ptr, 1, (1L << 0), handle_keys, gen_data);
}
