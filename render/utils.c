/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:42:31 by jel-yous          #+#    #+#             */
/*   Updated: 2025/11/02 19:47:54 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	put_pixel(t_img *img, int x, int y, unsigned int color)
{
	*(unsigned int *)(img->addr + (y * img->line_length
				+ x * (img->bits_per_pixel / 8))) = color;
}

void	cleanup(t_game_data *g)
{
	if (g->north_tex.img != NULL)
		mlx_destroy_image(g->mlx, g->north_tex.img);
	if (g->east_tex.img != NULL)
		mlx_destroy_image(g->mlx, g->east_tex.img);
	if (g->west_tex.img != NULL)
		mlx_destroy_image(g->mlx, g->west_tex.img);
	if (g->south_tex.img != NULL)
		mlx_destroy_image(g->mlx, g->south_tex.img);
	if (g->img.img != NULL)
		mlx_destroy_image(g->mlx, g->img.img);
	mlx_destroy_window(g->mlx, g->mlx_win);
	free_map(g->t_map);
}

unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	return (*(unsigned *)(img->addr
		+ (y * img->line_length + x * (img->bits_per_pixel / 8))));
}

void	exit_clean_game(t_game_data *game_data, int exit_code)
{
	cleanup(game_data);
	exit(exit_code);
}

int	get_rgb_color(int colors[3])
{
	return ((colors[0] << 16) | (colors[1] << 8) | (colors[2]));
}
