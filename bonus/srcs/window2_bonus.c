/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window1_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juhyelee <juhyelee@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:15:15 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/18 17:15:26 by juhyelee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	load_window(t_game *game)
{
	game->move_back = 0;
	game->move_front = 0;
	game->move_left = 0;
	game->move_right = 0;
	game->turn_left = 0;
	game->turn_right = 0;
	game->attack = 0;
	game->mlx = mlx_init();
	if (game->mlx == NULL)
		print_error(E_MLX);
	set_position(game, game->map.map);
	set_images(game, &game->screen, game->textures);
	load_sprite(&game->door, game->mlx, "texture/door.xpm");
	load_sprite(&game->fist[0], game->mlx, "texture/fist1.xpm");
	load_sprite(&game->fist[1], game->mlx, "texture/fist2.xpm");
	load_sprite(&game->fist[2], game->mlx, "texture/fist3.xpm");
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "cub3D");
	if (game->win == NULL)
		print_error(E_MLX);
	init_window(game->mlx, game->win, &game->screen, &game->rsrc);
	mlx_put_image_to_window(game->mlx, game->win, game->screen.obj, 0, 0);
}