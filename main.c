#include "cube3d.h"

void init_default_values(t_game_data *g)
{
    g->player.angle = M_PI/2;

    g->map_height = MAP_SIZE;
    g->map_width = MAP_SIZE;
    g->player.x = TILE_SIZE * 13;
    g->player.y = TILE_SIZE * 4;

    g->floor_color = MAT_GREY;
    g->ceil_color = LIGHT_BLUE_COLOR;

    g->key_event.a = 0;
    g->key_event.s = 0;
    g->key_event.d = 0;
    g->key_event.w = 0;
    g->key_event.left_arrow = 0;
    g->key_event.right_arrow = 0;

    g->img.img = mlx_new_image(g->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    g->img.addr = mlx_get_data_addr(g->img.img,
                                    &g->img.bits_per_pixel,
                                    &g->img.line_length,
                                    &g->img.endian);
    g->map = gen_map(MAP_SIZE);

    g->north_tex.img = mlx_xpm_file_to_image(g->mlx, "tex1.xpm", &g->north_tex.w, &g->north_tex.h);
    g->north_tex.addr = mlx_get_data_addr(g->north_tex.img, &g->north_tex.bits_per_pixel, &g->north_tex.line_length, &g->north_tex.endian);

    g->east_tex.img = mlx_xpm_file_to_image(g->mlx, "tex1.xpm", &g->east_tex.w, &g->east_tex.h);
    g->east_tex.addr = mlx_get_data_addr(g->east_tex.img, &g->east_tex.bits_per_pixel, &g->east_tex.line_length, &g->east_tex.endian);

    g->south_tex.img = mlx_xpm_file_to_image(g->mlx, "tex1.xpm", &g->south_tex.w, &g->south_tex.h);
    g->south_tex.addr = mlx_get_data_addr(g->south_tex.img, &g->south_tex.bits_per_pixel, &g->south_tex.line_length, &g->south_tex.endian);

    g->west_tex.img = mlx_xpm_file_to_image(g->mlx, "tex1.xpm", &g->west_tex.w, &g->west_tex.h);
    g->west_tex.addr = mlx_get_data_addr(g->west_tex.img, &g->west_tex.bits_per_pixel, &g->west_tex.line_length, &g->west_tex.endian);
}

int init_rays(t_game_data *game_data)
{
    int i;

    game_data->rays = malloc(sizeof(t_ray) * WINDOW_WIDTH);
    if (!game_data->rays)
    {
        return 0;
    }
    i = 0;
    while (i < WINDOW_WIDTH)
    {
        game_data->rays[i] = malloc(sizeof(t_ray));
        if (!game_data->rays[i])
        {
            while (i >= 0)
            {
                free(game_data->rays[i]);
                i--;
            }
            free(game_data->rays);
            return (0);
        }
        i++;
    }
    return (1);
}

void cast_rays(t_game_data *g)
{
    double angle;
    int i;

    angle = g->player.angle - ((FOV * M_PI / 180) / 2);
    i = 0;

    while (i < WINDOW_WIDTH)
    {
        g->rays[i]->angle = angle;
        angle += (FOV * M_PI / 180) / WINDOW_WIDTH;
        dda(g, g->rays[i]);
        i++;
    }
}

int render(t_game_data *g)
{
    static int counter;
    static int fps;
    long start_time = ft_gettime();

    cast_rays(g);
    render_game(g, g->rays);

    mlx_put_image_to_window(g->mlx, g->mlx_win, g->img.img, 0, 0);

    long end_time = ft_gettime();
    char *f = ft_itoa(fps);
    if (counter % 10 == 0)
    {
        fps = 1000 / (end_time - start_time);
        counter = 0;
    }
    mlx_string_put(g->mlx, g->mlx_win, 1, 10, 0xFFFFFF, f);
    free(f);
    player_movs(g);
    counter++;
    return (0);
}

// void f() { system("leaks cub"); }

int main(void)
{
    t_game_data game_data;

    game_data.mlx = mlx_init();
    game_data.mlx_win = mlx_new_window(game_data.mlx,
                                       WINDOW_WIDTH,
                                       WINDOW_HEIGHT,
                                       "cube 3d");
    init_default_values(&game_data);
    if (!game_data.mlx_win)
        return (1);
    if (!init_rays(&game_data))
        return (1);
    mlx_hook(game_data.mlx_win, ON_DESTROY, 0, on_destroy, &game_data);
    mlx_hook(game_data.mlx_win, ON_KEYDOWN, 0, on_key_down, &game_data);
    mlx_hook(game_data.mlx_win, ON_KEYUP, 0, on_key_up, &game_data);
    mlx_loop_hook(game_data.mlx, render, &game_data);
    mlx_loop(game_data.mlx);
    return (0);
}

