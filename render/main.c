/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jel-yous <jel-yous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 00:35:46 by jel-yous          #+#    #+#             */
/*   Updated: 2025/11/02 19:45:29 by jel-yous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	init_map(int argc, char **argv, t_map *map)
{
	if (argc != 2)
	{
		printf("Error\nUsage: %s <map.cub>\n", argv[0]);
		exit(1);
	}
	ft_bzero(map, sizeof(t_map));
	if (!parse_cub_file(argv[1], map))
	{
		printf("Error\nInvalid map file\n");
		free_map(map);
		exit(1);
	}
}

int	main(int argc, char **argv)
{
	t_game_data	game_data;
	t_map		map;

	ft_bzero(&game_data, sizeof(t_game_data));
	game_data.mlx = mlx_init();
	if (!game_data.mlx)
		return (1);
	game_data.mlx_win = mlx_new_window(game_data.mlx, WINDOW_WIDTH,
			WINDOW_HEIGHT, "cub 3d");
	if (!game_data.mlx_win)
		return (1);
	init_map(argc, argv, &map);
	init_game(&game_data, map);
	mlx_hook(game_data.mlx_win, ON_DESTROY, 0, on_destroy, &game_data);
	mlx_hook(game_data.mlx_win, ON_KEYDOWN, 0, on_key_down, &game_data);
	mlx_hook(game_data.mlx_win, ON_KEYUP, 0, on_key_up, &game_data);
	mlx_loop_hook(game_data.mlx, render, &game_data);
	mlx_loop(game_data.mlx);
	return (0);
}
