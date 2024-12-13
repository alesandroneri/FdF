#include "minilibx-linux/mlx.h"
#include <stdlib.h>

int main(void)
{
    void    *mlx_ptr; // Ponteiro que serve para efetuar a conexão com o servidor.

    mlx_ptr = mlx_init(); // Inicialização do servidor usando a função da mini_libx.
    if (mlx_ptr == NULL) // Verificação para caso o servidor não tenha inicializado corretamente.
        return (1);
    mlx_destroy_display(mlx_ptr); // Destroi o display e fecha.
    free(mlx_ptr); // Libera a memoria alocada para a variável apontada.
    return (0);
}
