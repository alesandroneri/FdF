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
#include <stdio.h>
#include <math.h>

// Struct para armazenar os pontos do mapa (valor de z e cor hexadecimal)
typedef struct s_point {
    int value;        // Valor da coordenada z
    char *hex;    // Cor do ponto em formato hexadecimal
} t_point;

// Struct para armazenar o estado do mouse
typedef struct s_mouse {
    int active_click; // Indica se o botão do mouse está pressionado
} t_mouse;

// Struct para gerenciar a imagem e a janela do mlx
typedef struct s_img {
    void *mlx;           // Ponteiro para o mlx
    void *win;           // Ponteiro para a janela
    void *img;           // Ponteiro para a imagem
    char *addr;          // Endereço da imagem
	int width;           // Largura da imagem
	int height;          // Altura da imagem
    int bpp;             // Bits por pixel
    int line_length;     // Bytes por linha da imagem
    int endian;          // Endianess da imagem
} t_img;

// Struct para armazenar o estado gráfico (zoom, translação, ângulos, etc.)
typedef struct s_graphics {
    int zoom;           // Fator de zoom para o mapa
    int shift_x;        // Translação no eixo X
    int shift_y;        // Translação no eixo Y
    float angle_x;      // Ângulo de rotação no eixo X
    float angle_y;      // Ângulo de rotação no eixo Y
    float angle_z;      // Ângulo de rotação no eixo Z
    float isometric_angle; // Ângulo para projeção isométrica
    float depth_factor; // Fator de profundidade
    int color;          // Cor padrão do mapa
} t_graphics;

// Struct principal do FDF que agrupa todas as informações
typedef struct s_fdf {
    int width;            // Largura do mapa
    int height;           // Altura do mapa
    t_point *z_matrix;    // Matriz de pontos (z) do mapa
    t_graphics graphics;  // Informações gráficas (zoom, rotação, etc.)
    t_img img;            // Informações de imagem e janela
    t_mouse mouse;        // Informações do mouse
    void *mlx_ptr;        // Ponteiro para o mlx
    void *win_ptr;        // Ponteiro para a janela do mlx
    int win_width;        // Largura da janela
    int win_height;       // Altura da janela
} t_fdf;

void read_file(char *file_name, t_fdf *data);
void bresenham(float x, float y, float x1, float y1, t_fdf *data);
void draw(t_fdf *data);

# endif
