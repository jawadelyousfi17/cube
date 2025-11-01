#ifndef CUBE3D_H
#define CUBE3D_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mlx.h>
#include "parse.h"

#define FOV 60
#define WINDOW_WIDTH 1000
#define WINDOW_HEIGHT 1000
#define ROT_SPEED 0.7
#define MOV_SPEED 5
#define TILE_SIZE 64

#define MAP_SIZE 20

enum
{
    ON_KEYDOWN = 2,
    ON_KEYUP = 3,
    ON_DESTROY = 17,
    LEFT_ARROW_KEY = 123,
    RIGHT_ARROW_KEY = 124,
    A_KEY = 0,
    W_KEY = 13,
    S_KEY = 1,
    D_KEY = 2,
    ESC_KEY = 53
};

enum
{
    NORTH,
    SOUTH,
    EAST,
    WEST
};

#define WHITE_COLOR 0xFFFFFF
#define BLACK_COLOR 0x000000
#define RED_COLOR 0xFF0000
#define GREEN_COLOR 0x00FF00
#define BLUE_COLOR 0x0000FF
#define YELLOW_COLOR 0xFFFF00
#define CYAN_COLOR 0xB3E5FC
#define MAGENTA_COLOR 0xFF00FF
#define LIGHT_GRAY_COLOR 0xD3D3D3
#define LIGHT_BLUE_COLOR 0xADD8E6
#define LIGHT_GREEN_COLOR 0x90EE90
#define LIGHT_PINK_COLOR 0xFFB6C1
#define MAT_GREY 0x455A64

typedef struct s_key_pressed
{
    int left_arrow;
    int right_arrow;
    int w;
    int s;
    int a;
    int d;
} t_key_press;

typedef struct s_img
{
    void *img;
    char *addr;
    int bits_per_pixel;
    int line_length;
    int endian;
    int w;
    int h;
} t_img;

typedef struct s_player
{
    double x;
    double y;
    double angle;
} t_player;

typedef struct s_ray
{
    double x;
    double y;
    double distance;
    int side;
    double angle;
    int direction;
    int hit;
    double wall_x;
} t_ray;

typedef struct s_game_data
{
    void *mlx;
    void *mlx_win;
    char **map;
    t_player player;
    t_img img;
    t_map *t_map;
    double tile_size;
    int map_width;
    int map_height;
    unsigned floor_color;
    unsigned ceil_color;
    t_key_press key_event;
    t_img north_tex;
    t_img south_tex;
    t_img west_tex;
    t_img east_tex;
} t_game_data;

typedef struct s_dda
{
    double xr;
    double yr;
    double xp;
    double yp;
    double step_x;
    double step_y;
} t_dda;




void init_game(t_game_data *g, t_map m);
int	get_rgb_color(int colors[3]);

void cleanup(t_game_data *game_data);
void exit_clean_game(t_game_data *game_data, int exit_code);

// keys evenets
int on_key_down(int key, t_game_data *game_data);
int on_key_up(int key, t_game_data *game_data);
int on_destroy(t_game_data *game_data);

// players movs
void player_movs(t_game_data *game_data);

// ray cast
void dda(t_game_data *g, t_ray *r);

// render game
int render(t_game_data *g);


// get image pixel
unsigned get_pixel_color(t_img *img, int x, int y);
void put_pixel(t_img *img, int x, int y, unsigned int color);



#endif