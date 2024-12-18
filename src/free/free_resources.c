#include "../../fdf.h"

void free_resources(t_gen_res *gen_data)
{
    if (gen_data->graphics)
        free(gen_data->graphics);
    if (gen_data->img)
        free(gen_data->img);
    if (gen_data->data)
        free(gen_data->data);
}