#include "cube3d.h"

#include <sys/time.h>
#include <string.h>

void draw_line(double start_x, double start_y, int len, double angle, t_img *img, unsigned color)
{
    int i;

    i = 0;
    while (i < len)
    {
        put_pixel(img, start_x, start_y, color);
        start_x += cos(angle);
        start_y += sin(angle);
        i++;
    }
}

void draw_square(double x, double y, int size_x, int size_y, t_img *img, unsigned color)
{
    int i;

    x = x - size_x / 2;
    y = y - size_y / 2;
    i = 0;
    while (i < size_y)
    {
        draw_line(x, y + i, size_x, 0, img, color);
        i++;
    }
}

char **gen_map(int map_size)
{
    int i;
    int j;
    char **map;

    int worldMap[20][20] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    map = malloc(sizeof(char *) * map_size);
    if (!map)
        return NULL;
    i = 0;
    while (i < map_size)
    {
        map[i] = malloc(sizeof(char) * map_size);
        if (!map[i])
            return NULL;
        j = 0;
        while (j < map_size)
        {
            if (i == 0 || j == 0 || i == map_size - 1 || j == map_size - 1)
                map[i][j] = '1';
            else
            {
                if (worldMap[i][j])
                    map[i][j] = '1';
                else
                    map[i][j] = worldMap[i][j];
            }
            j++;
        }
        i++;
    }

    return map;
}

void dda_draw_line(int x1, int y1, int x2, int y2, t_img *img, int color)
{
    int dx, dy, step, i = 1;
    double x_inc, y_inc, x = (double)x1, y = (double)y1;

    dx = x2 - x1;
    dy = y2 - y1;

    if (abs(dx) > abs(dy))
        step = abs(dx);
    else
        step = abs(dy);

    x_inc = (double)dx / step;
    y_inc = (double)dy / step;

    while (i <= step)
    {
        x += x_inc;
        y += y_inc;
        put_pixel(img, (int)x, (int)y, color);
        i++;
    }
}

int get_int_size(long int n)
{
    int counter;

    counter = 0;
    if (n == 0)
    {
        return (1);
    }
    while (n)
    {
        n /= 10;
        counter++;
    }
    return (counter);
}

char *ft_itoa(int n)
{
    long int nbr;
    int nbr_size;
    int is_negative;
    char *result;

    is_negative = 0;
    nbr = n;
    nbr_size = 0;
    if (nbr < 0)
    {
        is_negative = 1;
        nbr = -nbr;
        nbr_size++;
    }
    nbr_size += get_int_size(nbr);
    result = (char *)malloc((nbr_size + 1) * sizeof(char));
    result[nbr_size--] = '\0';
    while (nbr_size >= 0)
    {
        result[nbr_size--] = nbr % 10 + 48;
        nbr /= 10;
    }
    if (is_negative)
    {
        result[0] = '-';
    }
    return (result);
}

char *strjoin(char *s1, char *s2)
{
    char *s = malloc(strlen(s1) + strlen(s2) + 1);
    memcpy(s, s1, strlen(s1));
    memcpy(s + strlen(s1), s2, strlen(s2));
    s[(int)strlen(s1) + strlen(s2)] = 0;
    return s;
}

long long ft_gettime(void)
{
    struct timeval v;
    long long time;

    gettimeofday(&v, NULL);
    time = (v.tv_sec * 1000) + (v.tv_usec / 1000);
    return (time);
}

unsigned get_color_from_image(t_img *img, int x, int y)
{
    if (x > img->w || y > img->h)
        return 0;
    char *pixel = img->addr + (y * img->line_length) + (x * (img->bits_per_pixel) / 8);
    unsigned char r, gr, b;
    r = pixel[0];
    gr = pixel[1];
    b = pixel[2];
    unsigned color = ((r << 16) | (gr << 8) | b);
    return color;
}

