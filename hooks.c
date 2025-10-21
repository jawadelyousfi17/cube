#include "cube3d.h"

int on_destroy(t_game_data *game_data)
{
    cleanup(game_data);
    exit(0);
}
