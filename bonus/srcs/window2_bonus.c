/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taeoh <taeoh@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:15:15 by juhyelee          #+#    #+#             */
/*   Updated: 2024/04/18 17:37:37 by taeoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d_bonus.h"

void	sprite_images(t_game *game)
{
	game->spr.obj = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (game->spr.obj == NULL)
		print_error(E_XPM_FAIL);
	game->spr.addr = mlx_get_data_addr(game->spr.obj, &game->spr.bpp, \
									&game->spr.len, &game->spr.endian);
	flush_image(&game->spr);
	load_sprite(&game->coin[0], game->mlx, "texture/a.xpm");
	load_sprite(&game->coin[1], game->mlx, "texture/b.xpm");
	load_sprite(&game->coin[2], game->mlx, "texture/c.xpm");
	load_sprite(&game->coin[3], game->mlx, "texture/d.xpm");
	load_sprite(&game->coin[4], game->mlx, "texture/e.xpm");
}

void	set_images(t_game *game, t_img *sc, t_img *ts)
{
	sc->obj = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	if (sc->obj == NULL)
		print_error(E_XPM_FAIL);
	game->wall.obj = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	sc->addr = mlx_get_data_addr(sc->obj, &sc->bpp, &sc->len, &sc->endian);
	game->wall.addr = mlx_get_data_addr(game->wall.obj, &game->wall.bpp, \
										&game->wall.len, &game->wall.endian);
	set_png_images(game, ts, 0);
	set_png_images(game, ts, 1);
	set_png_images(game, ts, 2);
	set_png_images(game, ts, 3);
	sprite_images(game);
}

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
