/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:18:48 by aneri-da          #+#    #+#             */
/*   Updated: 2024/12/22 16:18:52 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	setup_variables(t_gen_res *gen_data)
{
	float	map_center_x;
	float	map_center_y;

	gen_data->graphics->zoom = 4;
	gen_data->graphics->angle_x = 0.2;
	gen_data->graphics->angle_y = 0.2;
	gen_data->graphics->depth_factor = 0.8;
	map_center_x = (gen_data->data->width - 1) * (gen_data->graphics->zoom
			/ 50);
	map_center_y = (gen_data->data->height - 1) * (gen_data->graphics->zoom
			/ 50);
	gen_data->graphics->shift_x = (gen_data->data->win_width / 2)
		- map_center_x;
	gen_data->graphics->shift_y = (gen_data->data->win_height / 2)
		- map_center_y;
}

int	init(t_gen_res *gen_data)
{
	gen_data->data->mlx_ptr = mlx_init();
	if (!gen_data->data->mlx_ptr)
		return (0);
	gen_data->data->win_width = 1920;
	gen_data->data->win_height = 1080;
	gen_data->data->win_ptr = NULL;
	gen_data->img->img_ptr = NULL;
	gen_data->img->img_data = NULL;
	mlx_get_screen_size(gen_data->data->mlx_ptr, &gen_data->data->win_width,
		&gen_data->data->win_height);
	if (gen_data->data->win_width < 0 || gen_data->data->win_height < 0)
		return (0);
	gen_data->data->win_ptr = mlx_new_window(gen_data->data->mlx_ptr,
			gen_data->data->win_width, gen_data->data->win_height, "FDF");
	if (!gen_data->data->win_ptr)
		return (0);
	setup_variables(gen_data);
	return (1);
}

int	malloc_structs_resources(t_gen_res *gen_data)
{
	gen_data->data = (t_fdf *)malloc(sizeof(t_fdf));
	if (!gen_data->data)
	{
		free_resources(gen_data);
		return (0);
	}
	gen_data->graphics = (t_graphics *)malloc(sizeof(t_graphics));
	if (!gen_data->graphics)
	{
		free_resources(gen_data);
		return (0);
	}
	gen_data->img = (t_img *)malloc(sizeof(t_img));
	if (!gen_data->img)
	{
		free_resources(gen_data);
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_gen_res	gen_data;

	if (ac != 2)
		return (ft_putendl_fd("Invalid number of arguments!", 2), 0);
	if (!malloc_structs_resources(&gen_data))
		return (ft_putendl_fd("Memory allocation of resources failed!", 2), 0);
	if (!read_file(av[1], gen_data.data))
		return (ft_putendl_fd("Failed to read the map!", 2), 1);
	if (init(&gen_data))
	{
		draw(&gen_data);
		setup_hooks(&gen_data);
		mlx_loop(gen_data.data->mlx_ptr);
	}
	free_server(&gen_data);
	free_resources(&gen_data);
	return (0);
}
