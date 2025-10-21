#include "cube3d.h"

void draw_ceil_floor(t_game_data *g, unsigned ceil_color, unsigned floor_color)
{
    t_img *img;
    int i;
    int j;

    img = &g->img;
    i = 0;
    while (i < WINDOW_HEIGHT / 2)
    {
        j = 0;
        while (j < WINDOW_WIDTH)
            put_pixel(img, j++, i, ceil_color);
        i++;
    }
    while (i < WINDOW_HEIGHT)
    {
        j = 0;
        while (j < WINDOW_WIDTH)
            put_pixel(img, j++, i, floor_color);
        i++;
    }
}


unsigned wall_color(t_ray *r, double factor, t_game_data *g)
{
    if (r->direction == NORTH)
        return get_pixel_color(&g->north_tex, r->wall_x * g->north_tex.w, (int)floor(factor * g->north_tex.h));
    if (r->direction == SOUTH)
        return get_pixel_color(&g->south_tex, r->wall_x * g->south_tex.w, (int)floor(factor * g->south_tex.h));
    if (r->direction == WEST)
        return get_pixel_color(&g->west_tex, r->wall_x * g->west_tex.w, (int)floor(factor * g->west_tex.h));

    return get_pixel_color(&g->east_tex, r->wall_x * g->east_tex.w, (int)floor(factor * g->east_tex.h));
}

void render_game(t_game_data *g, t_ray **rays)
{
    int w, h;


    draw_ceil_floor(g, LIGHT_BLUE_COLOR, MAT_GREY);
    for (int i = 0; i < WINDOW_WIDTH; i++)
    {
        double corrected_distance = rays[i]->distance * cos(- rays[i]->angle + g->player.angle);
        int lineHeight = (int)(((WINDOW_WIDTH / (2 * tan(FOV/2 * M_PI / 180)))) * TILE_SIZE) / corrected_distance;
        // int lineHeight = tan(FOV/2 * M_PI / 180) * 2 / corrected_distance;
        int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
        int wall_s = drawStart;
        if (drawStart < 0)
            drawStart = 0;
        int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
        if (drawEnd >= WINDOW_HEIGHT)
            drawEnd = WINDOW_HEIGHT - 1;

        for (int y = drawStart; y <= drawEnd; y++)
        {
        double factor = (double)(y - wall_s) / (lineHeight);
            int color = wall_color(rays[i], factor, g);
            put_pixel(&g->img, i, y, color);
        }
    }
}


