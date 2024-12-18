#include "keys.h"

// Função para mover o mapa
void movement_keys(int key, t_gen_res *gen_data)
{
    if(key == KEYCAP_A) // Move o mapa para a direita
        gen_data->graphics->shift_x -=10;
    if(key == KEYCAP_D) // Move o mapa para a esquerda
        gen_data->graphics->shift_x +=10;
    if(key == KEYCAP_W) // Move o mapa para cima
        gen_data->graphics->shift_y -=10;
    if(key == KEYCAP_S) // Move o mapa para baixo
        gen_data->graphics->shift_y +=10;
}
// Função para ajustar o zoom do mapa
void zoom_keys(int key, t_gen_res *gen_data)
{
    if (key == KEYCAP_PLUS_SIGN && gen_data->graphics->zoom < 21) // Aumenta o zoom
        gen_data->graphics->zoom += 1;
    if (key == KEYCAP_MINUS_SIGN && gen_data->graphics->zoom > 3) // Diminui o zoom
        gen_data->graphics->zoom -= 1;
    
}

// Função para ajustar o relevo do mapa
void depth_keys(int key, t_gen_res *gen_data)
{
    if (key == KEYCAP_NB_8) // Aumenta o relevo
        gen_data->graphics->depth_factor += 0.1;
    if (key == KEYCAP_NB_2) // Diminui o relevo
        gen_data->graphics->depth_factor -= 0.1;
}

// Função para rotacionar o mapa
void rotation_keys(int key, t_gen_res *gen_data)
{
    if (key == KEYCAP_ARROW_UP) // Rotaciona o mapa de baixo para cima.
        gen_data->graphics->angle_x += 0.1;
    if (key == KEYCAP_ARROW_DOWN) // Rotaciona o mapa de cima para baixo.
        gen_data->graphics->angle_x -= 0.1;
    if (key == KEYCAP_ARROW_RIGHT) // Rotaciona o mapa da esquerda para direita
        gen_data->graphics->angle_y += 0.1;
    if (key == KEYCAP_ARROW_LEFT) // Rotaciona o mapa da direita para a esquerda
        gen_data->graphics->angle_y -= 0.1;
}
void exit_keys(int key, t_gen_res *gen_data)
{
    if (key == KEYCAP_ESC)
    {
        mlx_destroy_window(gen_data->data->mlx_ptr, gen_data->data->win_ptr);
        free(gen_data->data->z_matrix);
        free(gen_data->data);
        free(gen_data);
        exit(0);
    }
        //return (gen_data->data->mlx_ptr);
}