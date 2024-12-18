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
#include "src/hook/keys.h"
#include <stdio.h>
#include <math.h>

// Struct para armazenar os pontos do mapa (valor de z e cor hexadecimal)
typedef struct s_point 
{
    int z_value; // Valor da coordenada z
    char *color_hex; // Cor do ponto em formato hexadecimal
} t_point;


// Struct com as coordenadas colocar os pixels na tela
typedef struct s_coordinates
{
    float x; // Coordenada 2D
    float x1; //Coordenada 2D do ponto final
    float y; //Coordenada 2D
    float y1; // Coordenada 2D do ponto final
    int z;  // Variável de profundidade
    int z1; // Variável de profundidade do ponto final
    int color; // Variável que armazena a cor a ser utilizada
} t_coordinates;

// Struct para gerenciar a imagem e a janela do mlx
typedef struct s_img 
{
    void *img_ptr; // Ponteiro para a imagem
    char *img_data; // Endereço da imagem
    int bpp; // Bits por pixel
    int line_length; // Bytes por linha da imagem
    int endian; // Endianess da imagem
} t_img;

// Struct para armazenar o estado gráfico (zoom, translação, ângulos, etc.)
typedef struct s_graphics 
{
    int zoom; // Fator de zoom para o mapa
    int shift_x; // Translação no eixo X
    int shift_y; // Translação no eixo Y
    float angle_x; // Ângulo de rotação no eixo X
    float angle_y; // Ângulo de rotação no eixo Y
    float depth_factor; // Fator de profundidade
} t_graphics;

// Struct principal do FDF que agrupa todas as informações
typedef struct s_fdf 
{
    int width; // Largura do mapa
    int height; // Altura do mapa
    int win_width; // Largura da janela
    int win_height; // Altura da janela
    t_point *z_matrix; // Matriz de pontos (z) do mapa
    void *mlx_ptr; // Ponteiro para o mlx
    void *win_ptr; // Ponteiro para a janela do mlx
} t_fdf;

// Struct para gerar os recursos das outras structs
typedef struct s_gen_res
{
    t_fdf *data;
    t_graphics *graphics;
    t_img *img;
} t_gen_res;

void read_file(char *file_name, t_fdf *data);
void bresenham(t_coordinates *coordinates, t_gen_res *gen_data);
void draw(t_gen_res *gen_data);


// Funções de liberação de memória
void    free_data(t_fdf *data);
void free_resources(t_gen_res *gen_data);

// Funções de hook
void movement_keys(int key, t_gen_res *gen_data);
void zoom_keys(int key, t_gen_res *gen_data);
void depth_keys(int key, t_gen_res *gen_data);
void rotation_keys(int key, t_gen_res *gen_data);
void exit_keys(int key, t_gen_res *gen_data);
void   setup_hooks(t_gen_res *gen_data);

# endif
