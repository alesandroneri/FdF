/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aneri-da <aneri-da@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 15:12:36 by aneri-da          #+#    #+#             */
/*   Updated: 2024/11/27 17:22:08 by aneri-da         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H

#include "libft/libft.h"
#include "minilibx-linux/mlx.h"
#include <math.h>

typedef struct s_point
{
	int	value; // alterar para z
	char *hex;
} t_point ;

typedef struct s_graph
{
	int zoom;
	int shift_x;
	int shift_y;

} t_graph ;

typedef struct s_mouse
{
	int active_click;

} t_mouse ;

typedef struct s_fdf
{
	int	width;
	int	height;
	//t_point	**z_matrix;
	t_point	*z_matrix;
	int zoom;
	int color;
	int shift_x;
	int shift_y;
	int keys[6];

	void	*mlx_ptr;
	void	*win_ptr;
}	t_fdf;

typedef struct s_img
{
	void *img_ptr;
	char *img_data;
	int	bpp;
	int len_line;

} t_img ;

typedef struct s_gen_wfm
{
	t_fdf *data;
	t_graph *graph;
	t_img	*img_data;
	t_mouse *mouse_set;
} t_gen_wfm ;

void read_file(char *file_name, t_fdf *data);
void bresenham(float x, float y, float x1, float y1, t_fdf *data);
void draw(t_fdf *data);

# endif
