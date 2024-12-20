#include "keys.h"
#include "../../fdf.h"

// // Evento de pressionar tecla
// int key_press(int key, t_key *keys) {
//     if (key == KEYCAP_ESC)
//         exit(0);
//     keys->keys[key] = true; // Marca a tecla como pressionada
//     return 0;
// }

// // Evento de soltar tecla
// int key_release(int key, t_key *keys) {
//     keys->keys[key] = false; // Marca a tecla como liberada
//     return 0;
// }
// Função para lidar com todos os eventos de teclado
static int handle_keys(int key, t_gen_res *gen_data)
{
    ft_printf("START - handle_keys\n");
    movement_keys(key, gen_data); // Chama a função que lida com movimentos no mapa
    zoom_keys(key, gen_data); // Chama a função que lida com ajuste de zoom no mapa
    depth_keys(key, gen_data); // Chama a função que lida com ajustes de relevo no mapa
    rotation_keys(key, gen_data); // Chama a função que lida com rotação do mapa
    exit_keys(key, gen_data); // Chama a função que lida com o fechamento do mapa pressionando o esc
    mlx_clear_window(gen_data->data->mlx_ptr, gen_data->data->win_ptr); // Destroi a imagem para atualizar o que ocorreu no mapa apos um hook
    draw(gen_data); // Desenha novamente o mapa atualizado 
    ft_printf("END - handle_keys\n");
    return (0);
}

// Função para aguardar os eventos que foram pré-determinados anteriormente e executar as ações necessárias
void   setup_hooks(t_gen_res *gen_data)
{
    ft_printf("START - setup_hooks\n");
    mlx_hook(gen_data->data->win_ptr, 17, 0, mlx_loop_end, gen_data->data->win_ptr); // Evento do botão "X"
	mlx_key_hook(gen_data->data->win_ptr, handle_keys, gen_data); // Eventos de teclado
    ft_printf("END - setup_hooks\n");
}

