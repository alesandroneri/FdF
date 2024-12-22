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

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include "src/hook/keys.h"
# include <math.h>
# include <stdio.h>

typedef struct s_point
{
	int			z_value;
	char		*color_hex;
}				t_point;

typedef struct s_coordinates
{
	float		x;
	float		x1;
	float		y;
	float		y1;
	int			z;
	int			z1;
	int			color;
}				t_coordinates;

typedef struct s_img
{
	void		*img_ptr;
	char		*img_data;
	int			bpp;
	int			line_length;
	int			endian;
}				t_img;

typedef struct s_graphics
{
	int			zoom;
	int			shift_x;
	int			shift_y;
	float		angle_x;
	float		angle_y;
	float		depth_factor;
}				t_graphics;

typedef struct s_fdf
{
	int			width;
	int			height;
	int			win_width;
	int			win_height;
	t_point		*z_matrix;
	void		*mlx_ptr;
	void		*win_ptr;
}				t_fdf;

typedef struct s_gen_res
{
	t_fdf		*data;
	t_graphics	*graphics;
	t_img		*img;
}				t_gen_res;

int				read_file(char *file_name, t_fdf *data);
void			draw(t_gen_res *gen_data);
int				maximum(int a, int b);
float			mod(float i);
void			initial_values(t_coordinates *coordinates, t_fdf *data);
void			isometric(float *x, float *y, int z, t_graphics *graphics);
void			put_pixel(t_coordinates *coordinates, t_gen_res *gen_data);
int				get_text_size(char *str);
void			draw_text(t_coordinates *coordinates, char *text, char *value,
					t_gen_res *gen_data);
void			draw_panel_info(t_gen_res *gen_data);
void			center_map(t_coordinates *coordinates, t_gen_res *gen_data);
void			zoom(t_coordinates *coordinates, t_graphics *graphics);
void			shift(t_coordinates *coordinates, t_graphics *graphics);
void			free_data(t_fdf *data);
void			free_resources(t_gen_res *gen_data);
void			free_server(t_gen_res *gen_data);
int				movement_keys(int key, t_gen_res *gen_data);
int				zoom_keys(int key, t_gen_res *gen_data);
int				depth_keys(int key, t_gen_res *gen_data);
int				rotation_keys(int key, t_gen_res *gen_data);
void			setup_hooks(t_gen_res *gen_data);
void			free_image(t_gen_res *gen_data);
int				ft_count_words(char const *str, char sep);

#endif
