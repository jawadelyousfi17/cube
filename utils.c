#include "cube3d.h"


void put_pixel(t_img *img, int x, int y, unsigned int color)
{
    char *dst;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}


void cleanup(t_game_data *game_data)
{
    int i;

    i = 0;
    while (i < WINDOW_WIDTH)
    {
        free(game_data->rays[i]);
        i++;
    }
    free(game_data->rays);
    mlx_destroy_image(game_data->mlx, game_data->img.img);
    mlx_destroy_window(game_data->mlx, game_data->mlx_win);
}

unsigned get_pixel_color(t_img *img, int x, int y)
{
    int bytes_per_pixel = img->bits_per_pixel / 8;
    char *pixel = img->addr + (y * img->line_length + x * bytes_per_pixel);


    unsigned char r, g, b;
        r = pixel[0];
        g = pixel[1];
        b = pixel[2];

    return ((r << 16) | (g << 8) | b);
}