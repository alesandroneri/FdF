/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:20:57 by aneri-da          #+#    #+#             */
/*   Updated: 2024/12/22 16:21:04 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../fdf.h"

void	free_data(t_fdf *data)
{
	int	i;

	i = 0;
	if (!data || !data->height)
		return ;
	if (data->z_matrix)
	{
		while (i < data->height * data->width)
		{
			free(data->z_matrix[i].color_hex);
			i++;
		}
		free(data->z_matrix);
	}
	if (data->mlx_ptr)
		free(data->mlx_ptr);
	if (data->win_ptr)
		free(data->win_ptr);
	free(data);
}

void	free_resources(t_gen_res *gen_data)
{
	if (gen_data->graphics)
		free(gen_data->graphics);
	if (gen_data->img)
	{
		free(gen_data->img);
	}	
	if (gen_data->data)
		free(gen_data->data);
}

void	free_server(t_gen_res *gen_data)
{
	if (!gen_data->data)
		return ;
	if (gen_data->img->img_data)
		mlx_destroy_image(gen_data->data->mlx_ptr, gen_data->img->img_ptr);
	if (gen_data->data->win_ptr)
	{
		mlx_destroy_window(gen_data->data->mlx_ptr, gen_data->data->win_ptr);
		gen_data->data->win_ptr = NULL;
	}
	if (gen_data->data->mlx_ptr)
	{
		mlx_destroy_display(gen_data->data->mlx_ptr);
		free(gen_data->data->mlx_ptr);
		gen_data->data->mlx_ptr = NULL;
	}
	if (gen_data->data)
		free_data(gen_data->data);
	gen_data->data = NULL;
}
